/*
 *	@File	Transition.cpp
 *	@Brief	場面切り替えのトランジション。
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#include "pch.h"

#include "Transition.h"

 //==============================================================================
 // インプットレイアウトの作成
 //==============================================================================
const std::vector<D3D11_INPUT_ELEMENT_DESC> Transition::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

//==============================================================================
// コンストラクタ
//==============================================================================
Transition::Transition()
	: m_vertice{}
	, m_color{}
{
}

//==============================================================================
// デストラクタ
//==============================================================================
Transition::~Transition()
{
}

//==============================================================================
// 作成関数
//==============================================================================
void Transition::Create(const wchar_t* path)
{
	// デバイスリソースを取得
	auto _pDR = DX::DeviceResources::GetInstance();

	// 画像の読み込み
	LoadTexture(path);

	// シェーダーの作成
	CreateShader();

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(_pDR->GetD3DDeviceContext());

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(_pDR->GetD3DDevice());
}

//==============================================================================
// テクスチャの読み込み
//==============================================================================
void Transition::LoadTexture(const wchar_t* path)
{
	// 画像を読み込む
	auto _pDR = DX::DeviceResources::GetInstance();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(_pDR->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture = texture;
}

//==============================================================================
// シェーダーの作成
//==============================================================================
void Transition::CreateShader()
{
	// デバイスを取得
	auto _pDR = DX::DeviceResources::GetInstance();
	auto _device = _pDR->GetD3DDevice();

	// シェーダーファイルの読み込み
	std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/Transition/VS_Transition.cso");
	_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> _gs = DX::ReadData(L"Resources/Shaders/Transition/GS_Transition.cso");
	_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/Transition/PS_Transition.cso");
	_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// インプットレイアウトの作成
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_vs.data(), _vs.size(), m_inputLayout.GetAddressOf());

	// シェーダーの作成
	_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	_device->CreateGeometryShader(_gs.data(), _gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// コンスタントバッファの作成
	CreateConstBuffer();
}

//==============================================================================
// コンスタントバッファの作成
//==============================================================================
void Transition::CreateConstBuffer()
{
	DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();
	auto _device = _pDR->GetD3DDevice();

	// コンスタントバッファを作成する
	D3D11_BUFFER_DESC _buffDesc = {};
	ZeroMemory(&_buffDesc, sizeof(_buffDesc));
	_buffDesc.Usage = D3D11_USAGE_DEFAULT;
	_buffDesc.ByteWidth = sizeof(ConstBuffer);
	_buffDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_buffDesc.CPUAccessFlags = NULL;
	_device->CreateBuffer(&_buffDesc, nullptr, &m_constBuffer);
}

//==============================================================================
// 描画処理
//==============================================================================
void Transition::Render(const float& timer)
{
	DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// 頂点情報
	VertexPositionColorTexture _vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero,	// 頂点の位置
		SimpleMath::Vector4::One,	// 色情報
		SimpleMath::Vector2::Zero	// テクスチャの位置
		)
	};

	//シェーダーに渡すバッファを作成する
	ConstBuffer _throwBuff;
	_throwBuff.Diffuse = m_color;
	_throwBuff.Time = SimpleMath::Vector4(timer, 0, 0, 0);

	// ConstBufferからID3D11Bufferへの変換
	_context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &_throwBuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* _buffer[1] = { m_constBuffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _buffer);
	_context->GSSetConstantBuffers(0, 1, _buffer);
	_context->PSSetConstantBuffers(0, 1, _buffer);

	// 画像用サンプラーの登録
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// 透明判定処理
	_context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングは左周り
	_context->RSSetState(m_states->CullNone());

	// シェーダをセットする
	_context->VSSetShader(m_verShader.Get(), nullptr, 0);
	_context->GSSetShader(m_geoShader.Get(), nullptr, 0);
	_context->PSSetShader(m_pixShader.Get(), nullptr, 0);

	// ピクセルシェーダにテクスチャを登録する。
	_context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// インプットレイアウトの登録
	_context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, _vertex, 4);
	m_batch->End();

	// シェーダの登録を解除
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}