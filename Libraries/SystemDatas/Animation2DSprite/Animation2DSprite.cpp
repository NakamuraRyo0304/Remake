/*
 *	@File	Animation2DSprite.cpp
 *	@Brief	2Dスプライトのアニメーションクラス。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Animation2DSprite.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Animation2DSprite::Animation2DSprite()
	: m_position{ SimpleMath::Vector3::Zero }	// ワールド座標
{
}

//==============================================================================
// デストラクタ
//==============================================================================
Animation2DSprite::~Animation2DSprite()
{
	m_states.reset();
	m_batch.reset();
	m_shaders.reset();
	m_srv.Reset();
}

//==============================================================================
// リソースの作成
//==============================================================================
void Animation2DSprite::CreateResources(const wchar_t* path)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	m_batch = std::make_unique<PrimitiveVertex>(_context);
	m_states = std::make_unique<CommonStates>(_device);
	m_shaders = std::make_unique<Shaders>();

	// 画像ファイルを読み込む
	CreateDDSTextureFromFile(_device, path, nullptr, m_srv.ReleaseAndGetAddressOf());

	// コンスタントバッファの作成
	CreateConstBuffer();

	// シェーダー・インプットレイアウトの作成
	CreateInputLayout(CreateShaders());
}

//==============================================================================
// 描画関数
//==============================================================================
void Animation2DSprite::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 頂点情報を初期化する
	VertexPositionColorTexture _vertex =
		VertexPositionColorTexture(SimpleMath::Vector3::Zero, SimpleMath::Vector4::One, SimpleMath::Vector2::Zero);

	// 座標を更新
	_vertex.position = m_position;

	// シェーダーにコンスタントバッファを渡す
	ConstBuffer _buffer;
	_buffer.View = view.Transpose();
	_buffer.Proj = proj.Transpose();
	_buffer.World = m_world.Transpose();
	_buffer.Move = SimpleMath::Vector4::One;

	// 受け渡し用バッファの内容更新(ConstBufferからID3D11Bufferへの変換）
	_context->UpdateSubresource(m_buffer.Get(), 0, NULL, &_buffer, 0, 0);

	//シェーダーにバッファを渡す
	ID3D11Buffer* _cbuffer[1] = { m_buffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _cbuffer);
	_context->GSSetConstantBuffers(0, 1, _cbuffer);
	_context->PSSetConstantBuffers(0, 1, _cbuffer);

	// 画像用サンプラーの登録
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// 半透明描画指定
	ID3D11BlendState* _blendState = m_states->NonPremultiplied();

	// 透明判定処理(色がないところは透明化する)
	_context->OMSetBlendState(_blendState, nullptr, 0xFFFFFFFF);

	// オブジェクトの前後関係を有効化
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングは左周り
	_context->RSSetState(m_states->CullNone());

	// シェーダをセットする
	_context->VSSetShader(m_shaders->VS.Get(), nullptr, 0);
	_context->GSSetShader(m_shaders->GS.Get(), nullptr, 0);
	_context->PSSetShader(m_shaders->PS.Get(), nullptr, 0);

	//ピクセルシェーダにテクスチャを登録する
	_context->PSSetShaderResources(0, 1, m_srv.GetAddressOf());

	//インプットレイアウトの登録
	_context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &_vertex, 1);
	m_batch->End();

	//シェーダの解放
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// ビルボード化関数(Draw関数より前に呼び出す)
//==============================================================================
void Animation2DSprite::CreateBillboard(SimpleMath::Vector3 eye, SimpleMath::Vector3 target, SimpleMath::Vector3 up)
{
	m_world = SimpleMath::Matrix::CreateBillboard(SimpleMath::Vector3::Zero, eye - target, up);

	// 回転を止めて常に正面に向ける
	SimpleMath::Matrix _rot = SimpleMath::Matrix::Identity;
	_rot._11 = -1;
	_rot._33 = -1;

	// ビルボードのテクスチャを回転
	m_world = _rot * m_world;
}

//==============================================================================
// コンスタントバッファの作成
//==============================================================================
void Animation2DSprite::CreateConstBuffer()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// 空のコンスタントバッファを作成
	D3D11_BUFFER_DESC _buffer = {};
	ZeroMemory(&_buffer, sizeof(_buffer));

	// バッファの設定
	_buffer.Usage = D3D11_USAGE_DEFAULT;					// 読み書きのモードをデフォルトにする
	_buffer.ByteWidth = sizeof(ConstBuffer);				// 定数バッファのサイズを格納
	_buffer.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// 定数バッファとして使用
	_buffer.CPUAccessFlags = NULL;							// CPUから書き換えを制限
	_device->CreateBuffer(&_buffer, nullptr, &m_buffer);	// 作成したバッファを格納
}

//==============================================================================
// シェーダーの作成
//==============================================================================
std::vector<uint8_t> Animation2DSprite::CreateShaders()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// ピクセルシェーダー作成
	std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/Normal/NormalPS.cso");
	DX::ThrowIfFailed(_device->CreatePixelShader(
		_ps.data(), _ps.size(), nullptr, m_shaders->PS.ReleaseAndGetAddressOf()));

	// 頂点シェーダー作成
	std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/Normal/NormalVS.cso");
	DX::ThrowIfFailed(_device->CreateVertexShader(
		_vs.data(), _vs.size(), nullptr, m_shaders->VS.ReleaseAndGetAddressOf()));

	// ジオメトリシェーダー作成
	std::vector<uint8_t> _gs = DX::ReadData(L"Resources/Shaders/Normal/NormalGS.cso");
	DX::ThrowIfFailed(_device->CreateGeometryShader(
		_gs.data(), _gs.size(), nullptr, m_shaders->GS.ReleaseAndGetAddressOf()));

	// すべて読み込んだら頂点シェーダーを返却
	return _vs;
}

//==============================================================================
// インプットレイアウトの作成
//==============================================================================
void Animation2DSprite::CreateInputLayout(std::vector<uint8_t> vs)
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	DX::ThrowIfFailed(_device->CreateInputLayout(
		&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf()));
}

