/*
 *  @File   Water.cpp
 *  @Brief  水面。
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Water.h"

//==============================================================================
// 定数の設定
//==============================================================================
// インプットレイアウト
const std::vector<D3D11_INPUT_ELEMENT_DESC> Water::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const float Water::WATER_SCALE = 40.0f;	// 画像のスケール
const UINT Water::VERTEX_NUM = 16;		// 頂点数

//==============================================================================
// コンストラクタ
//==============================================================================
Water::Water()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// コンスタントバッファ生成
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(WaterConstant);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_waterConstantBuffer);

	// コンスタントバッファの値渡し
	WaterConstant _cbuffer = {};
	_cbuffer.Scale = WATER_SCALE;
	_context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &_cbuffer, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* _buffer[1] = { m_waterConstantBuffer.Get() };
	_context->VSSetConstantBuffers(1, 1, _buffer);
	_context->GSSetConstantBuffers(1, 1, _buffer);
	_context->PSSetConstantBuffers(1, 1, _buffer);
}

//==============================================================================
// デストラクタ
//==============================================================================
Water::~Water()
{
	m_primitive.reset();
	m_states.reset();
}

//==============================================================================
// 生成関数
//==============================================================================
void Water::Create(const wchar_t* path)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// シェーダーの作成
	CreateShader();

	// 画像の読み込み
	LoadTexture(path);

	// プリミティブバッチの作成
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(_context);

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(_device);
}

//==============================================================================
// 描画関数
//==============================================================================
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 板ポリゴンの頂点情報
	VertexPositionColorTexture _vertex[VERTEX_NUM] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector4::One,
		SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// コンスタントバッファの値渡し
	ConstantBuffer _cbuffer = {};
	_cbuffer.View = view.Transpose();
	_cbuffer.Proj = proj.Transpose();
	_cbuffer.World = m_world.Transpose();
	_cbuffer.Time = _timer;
	_context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &_cbuffer, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* _buffer[1] = { m_constantBuffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _buffer);
	_context->GSSetConstantBuffers(0, 1, _buffer);
	_context->PSSetConstantBuffers(0, 1, _buffer);

	// サンプラーステートの設定
	ID3D11SamplerState* _sampler[1] = { m_states->LinearWrap() };
	_context->PSSetSamplers(0, 1, _sampler);

	// 透過処理の設定
	ID3D11BlendState* _blendstate = m_states->NonPremultiplied();
	_context->OMSetBlendState(_blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// 裏面は映らないためカリング
	_context->RSSetState(m_states->CullClockwise());

	// シェーダを設定
	_context->VSSetShader(m_vs.Get(), nullptr, 0);
	_context->GSSetShader(m_gs.Get(), nullptr, 0);
	_context->PSSetShader(m_ps.Get(), nullptr, 0);

	// ピクセルシェーダにテクスチャを登録
	for (UINT i = 0; i < m_texture.size(); i++)
	{
		_context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// インプットレイアウトの登録
	_context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_primitive->Begin();
	m_primitive->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &_vertex[0], 4);
	m_primitive->End();

	// シェーダの登録を解除
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// テクスチャ読み込み関数
//==============================================================================
void Water::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(DX::DeviceResources::GetInstance()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture.push_back(texture);
}


//==============================================================================
// シェーダー作成
//==============================================================================
void Water::CreateShader()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	auto _vs = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto _gs = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto _ps = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	// インプットレイアウトの作成
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_vs.data(), _vs.size(), m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vs.data(), _vs.size(), NULL, m_vs.ReleaseAndGetAddressOf()));

	// ジオメトリシェーダ作成
	DX::ThrowIfFailed(
		_device->CreateGeometryShader(_gs.data(), _gs.size(), NULL, m_gs.ReleaseAndGetAddressOf()));

	// ピクセルシェーダ作成
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_ps.data(), _ps.size(), NULL, m_ps.ReleaseAndGetAddressOf()));

	// シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(ConstantBuffer);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_constantBuffer);
}