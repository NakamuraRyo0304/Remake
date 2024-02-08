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

//==============================================================================
// コンストラクタ
//==============================================================================
Water::Water()
{
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(WaterConstant);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_waterConstantBuffer);

	// コンスタントバッファの作成
	WaterConstant _cbuff = {};
	_cbuff.Scale = 10.0f;
	_context->UpdateSubresource(m_waterConstantBuffer.Get(), 0, NULL, &_cbuff, 0, 0);

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
}

//==============================================================================
// 生成関数
//==============================================================================
void Water::Create(const wchar_t* path)
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// シェーダーの作成
	CreateShader();

	// 画像の読み込み
	LoadTexture(path);

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);
}

//==============================================================================
// 描画関数
//==============================================================================
void Water::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 頂点情報(板ポリゴンの４頂点の座標情報）
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector4::One,
		SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// コンスタントバッファの作成
	ConstantBuffer cbuff = {};
	cbuff.View = view.Transpose();
	cbuff.Proj = proj.Transpose();
	cbuff.World = m_world.Transpose();
	cbuff.Time = _timer;

	// 受け渡し用バッファの内容更新
	context->UpdateSubresource(m_constantBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// シェーダーにバッファを渡す
	ID3D11Buffer* cb[1] = { m_constantBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// 画像用サンプラーの登録(シェーダーのSamLinear)
	// Linear ぼやかす Point くっきり
	// Wrap ループさせる Clamp 0-1意外は適当に塗られる
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// 半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングはなし
	context->RSSetState(m_states->CullNone());

	// シェーダを設定
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	// ピクセルシェーダにテクスチャを登録
	for (int i = 0; i < m_texture.size(); i++)
	{
		context->PSSetShaderResources(i, 1, m_texture[i].GetAddressOf());
	}

	// インプットレイアウトの登録
	context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	// シェーダの登録を解除
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
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
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	auto VSData = DX::ReadData(L"Resources/Shaders/Water/WaterVS.cso");
	auto GSData = DX::ReadData(L"Resources/Shaders/Water/WaterGS.cso");
	auto PSData = DX::ReadData(L"Resources/Shaders/Water/WaterPS.cso");

	//インプットレイアウトの作成
	device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		VSData.data(), VSData.size(), m_inputLayout.GetAddressOf());

	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.data(), VSData.size(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}

	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.data(), GSData.size(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.data(), PSData.size(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	//シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_constantBuffer);
}