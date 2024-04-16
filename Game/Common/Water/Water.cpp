/*
 *  @File   Water.cpp
 *  @Brief  水面。
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Water.h"

// インプットレイアウト
const std::vector<D3D11_INPUT_ELEMENT_DESC> Water::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3)+ sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

const float Water::SCALE = 40.0f;	// 画像のスケール
const UINT Water::VERTEX_NUM = 16;	// 頂点数

// コンストラクタ
Water::Water()
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// コンスタントバッファ生成
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(WaterConstant);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_waterConstantBuffer);

	// コンスタントバッファの値渡し
	WaterConstant cbuff = {};
	cbuff.Scale = SCALE;
	context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* buff[1] = { m_waterConstantBuffer.Get() };
	context->VSSetConstantBuffers(1, 1, buff);
	context->GSSetConstantBuffers(1, 1, buff);
	context->PSSetConstantBuffers(1, 1, buff);
}

// デストラクタ
Water::~Water()
{
	m_primitive.reset();
	m_states.reset();
}

// 生成
void Water::Create(const wchar_t* path)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// シェーダーの作成
	CreateShader();
	// 画像の読み込み
	LoadTexture(path);
	// プリミティブバッチの作成
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);
}

// 描画
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 板ポリゴンの頂点情報
	VertexPositionColorTexture vertex[VERTEX_NUM] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero, SimpleMath::Vector4::One, SimpleMath::Vector2::Zero),
	};

	// コンスタントバッファの値渡し
	ConstantBuffer cbuff = {};
	cbuff.View = view.Transpose();
	cbuff.Proj = proj.Transpose();
	cbuff.World = m_world.Transpose();
	cbuff.Time = timer;
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* buff[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, buff);
	context->GSSetConstantBuffers(0, 1, buff);
	context->PSSetConstantBuffers(0, 1, buff);

	// サンプラーステートの設定
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// 透過処理の設定
	ID3D11BlendState* blendState = m_states->NonPremultiplied();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// 裏面は映らないためカリング
	context->RSSetState(m_states->CullClockwise());

	// シェーダを設定
	context->VSSetShader(m_vs.Get(), nullptr, 0);
	context->GSSetShader(m_gs.Get(), nullptr, 0);
	context->PSSetShader(m_ps.Get(), nullptr, 0);

	// ピクセルシェーダにテクスチャを登録
	for (UINT i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_primitive->Begin();
	m_primitive->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_primitive->End();

	// シェーダの登録を解除
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}

// テクスチャ読み込み関数
void Water::LoadTexture(const wchar_t* path)
{
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(DX::DeviceResources::GetInstance()->GetD3DDevice(),
		path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture.push_back(texture);
}

// シェーダー作成
void Water::CreateShader()
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	auto vs = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto gs = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto ps = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	// インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	DX::ThrowIfFailed(
		device->CreateVertexShader(vs.data(), vs.size(), NULL, m_vs.ReleaseAndGetAddressOf()));

	// ジオメトリシェーダ作成
	DX::ThrowIfFailed(
		device->CreateGeometryShader(gs.data(), gs.size(), NULL, m_gs.ReleaseAndGetAddressOf()));

	// ピクセルシェーダ作成
	DX::ThrowIfFailed(
		device->CreatePixelShader(ps.data(), ps.size(), NULL, m_ps.ReleaseAndGetAddressOf()));

	// シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstantBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_constantBuffer);
}