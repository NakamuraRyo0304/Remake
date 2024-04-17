/*
 *	@File	Transition.cpp
 *	@Brief	場面切り替えのトランジション。
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Transition.h"

 // インプットレイアウトの作成
const std::vector<D3D11_INPUT_ELEMENT_DESC> Transition::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(SimpleMath::Vector3) + sizeof(SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// コンストラクタ
Transition::Transition()
	:
	m_vertice(),
	m_color()
{
}

// デストラクタ
Transition::~Transition()
{
}

// 作成
void Transition::Create(const wchar_t* path)
{
	// デバイスリソースを取得
	auto pDR = DX::DeviceResources::GetInstance();

	// 画像の読み込み
	LoadTexture(path);

	// シェーダーの作成
	CreateShader();

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(pDR->GetD3DDeviceContext());

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(pDR->GetD3DDevice());
}

// テクスチャの読み込み
void Transition::LoadTexture(const wchar_t* path)
{
	// 画像を読み込む
	auto pDR = DX::DeviceResources::GetInstance();
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
	CreateWICTextureFromFile(pDR->GetD3DDevice(), path, nullptr, texture.ReleaseAndGetAddressOf());
	m_texture = texture;
}

// シェーダーの作成
void Transition::CreateShader()
{
	// デバイスを取得
	auto pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// シェーダーファイルの読み込み
	std::vector<uint8_t> vs = DX::ReadData(L"Resources/Shaders/Transition/VS_Transition.cso");
	device->CreateVertexShader(vs.data(), vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> gs = DX::ReadData(L"Resources/Shaders/Transition/GS_Transition.cso");
	device->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	std::vector<uint8_t> ps = DX::ReadData(L"Resources/Shaders/Transition/PS_Transition.cso");
	device->CreatePixelShader(ps.data(), ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		vs.data(), vs.size(), m_inputLayout.GetAddressOf());

	// シェーダーの作成
	device->CreateVertexShader(vs.data(), vs.size(), nullptr, m_verShader.ReleaseAndGetAddressOf());
	device->CreateGeometryShader(gs.data(), gs.size(), nullptr, m_geoShader.ReleaseAndGetAddressOf());
	device->CreatePixelShader(ps.data(), ps.size(), nullptr, m_pixShader.ReleaseAndGetAddressOf());

	// コンスタントバッファの作成
	CreateConstBuffer();
}

// コンスタントバッファの作成
void Transition::CreateConstBuffer()
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto device = pDR->GetD3DDevice();

	// コンスタントバッファを作成する
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ConstBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = NULL;
	device->CreateBuffer(&desc, nullptr, &m_constBuffer);
}

// 描画
void Transition::Draw(const float& timer)
{
	DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();
	auto context = pDR->GetD3DDeviceContext();

	// 頂点情報
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3::Zero,	// 頂点の位置
		SimpleMath::Vector4::One,	// 色情報
		SimpleMath::Vector2::Zero	// テクスチャの位置
		)
	};

	// シェーダーに渡すバッファを作成
	ConstBuffer cbuff;
	cbuff.Diffuse = m_color;
	cbuff.Time = SimpleMath::Vector4(timer, 0, 0, 0);

	context->UpdateSubresource(m_constBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* buff[1] = { m_constBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, buff);
	context->GSSetConstantBuffers(0, 1, buff);
	context->PSSetConstantBuffers(0, 1, buff);

	// 画像用サンプラーの登録
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// 透明判定処理
	context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	// シェーダをセットする
	context->VSSetShader(m_verShader.Get(), nullptr, 0);
	context->GSSetShader(m_geoShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixShader.Get(), nullptr, 0);

	// ピクセルシェーダにテクスチャを登録する。
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, vertex, 4);
	m_batch->End();

	// シェーダの登録を解除
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}