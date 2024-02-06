/*
 *  @File   ShadowMap.cpp
 *  @Brief  シャドウマップ。
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"
#include "ShadowMap.h"

//==============================================================================
// コンストラクタ
//==============================================================================
ShadowMap::ShadowMap(CommonStates* states)
	: m_lightTheta{ 0.0f }	// ライト角度
{
	// スポットライトの範囲
	m_lightTheta = 85.0f;

	// ライトの位置
	m_lightPosition = SimpleMath::Vector3(4.5f, 10.0f, 10.0f);

	// ライトの回転
	m_lightRotate = SimpleMath::Quaternion(0.80f, 0.30f, -0.20f, 0.50f);

	//==============================================================================
	// シャドウマップ関連の作成
	//==============================================================================
	RECT _rect = { 0, 0, SHADOWMAP_SIZE, SHADOWMAP_SIZE };
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// レンダーテクスチャの作成
	m_renderTexture = std::make_unique<DX::RenderTexture>(DXGI_FORMAT_R32_FLOAT);
	m_renderTexture->SetDevice(_device);
	m_renderTexture->SetWindow(_rect);

	// デプスステンシルの作成
	m_depthStencil = std::make_unique<DepthStencil>(DXGI_FORMAT_D32_FLOAT);
	m_depthStencil->SetDevice(_device);
	m_depthStencil->SetWindow(_rect);

	// デプス頂点シェーダーの作成
	std::vector<uint8_t> _vsDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS_Depth.cso");
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vsDep.data(), _vsDep.size(), nullptr, m_vsDep.ReleaseAndGetAddressOf())
	);

	// デプスピクセルシェーダーの作成
	std::vector<uint8_t> _psDep = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS_Depth.cso");
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_psDep.data(), _psDep.size(), nullptr, m_psDep.ReleaseAndGetAddressOf())
	);

	//////////////////////////////////////////////////////////////////////////////////
	// 定数バッファ作成手順(頻繁)			 //	定数バッファ作成手順(極稀)			//
	// [Shadow]								 //	[LightFov]							//
	// ①GPU・CPUからのアクセスを許可		 //	①GPU側のみアクセス許可				//
	// ②リソースはダイナミック				 //	②リソースはデフォルト				//
	// ③CPU側から書き込みをできるように設定 //	③CPUのアクセスは制限する			//
	//////////////////////////////////////////////////////////////////////////////////

	// シャドウバッファの作成
	{
		D3D11_BUFFER_DESC _desc = {};
		_desc.ByteWidth = static_cast<UINT>(sizeof(ShadowBuffer));
		_desc.Usage = D3D11_USAGE_DYNAMIC;
		_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		DX::ThrowIfFailed(_device->CreateBuffer(&_desc, nullptr, m_shadowConstant.ReleaseAndGetAddressOf()));
	}

	// ライトフォブバッファの作成
	{
		D3D11_BUFFER_DESC _desc = {};
		_desc.ByteWidth = static_cast<UINT>(sizeof(LightFovBuffer));
		_desc.Usage = D3D11_USAGE_DEFAULT;
		_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		_desc.CPUAccessFlags = 0;
		DX::ThrowIfFailed(_device->CreateBuffer(&_desc, nullptr, m_lightConstant.ReleaseAndGetAddressOf()));
	}

	// 頂点シェーダーの作成
	std::vector<uint8_t> _vs = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_VS.cso");
	DX::ThrowIfFailed(
		_device->CreateVertexShader(_vs.data(), _vs.size(), nullptr, m_vs.ReleaseAndGetAddressOf())
	);

	// ピクセルシェーダーの作成
	std::vector<uint8_t> _ps = DX::ReadData(L"Resources/Shaders/ShadowMap/SM_PS.cso");
	DX::ThrowIfFailed(
		_device->CreatePixelShader(_ps.data(), _ps.size(), nullptr, m_ps.ReleaseAndGetAddressOf())
	);

	// サンプラーの作成
	{
		D3D11_SAMPLER_DESC _desc = CD3D11_SAMPLER_DESC(D3D11_DEFAULT);
		_desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
		_desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
		_desc.ComparisonFunc = D3D11_COMPARISON_LESS;
		_device->CreateSamplerState(&_desc, m_sampler.ReleaseAndGetAddressOf());
	}
	m_linearWrap = states->LinearWrap();
}

//==============================================================================
// デストラクタ
//==============================================================================
ShadowMap::~ShadowMap()
{
}

//==============================================================================
// ライトバッファの初期化
//==============================================================================
void ShadowMap::Initialize()
{
	// ライトバッファの更新
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	LightFovBuffer _lightBuff = {};
	_lightBuff.fCosTheta = cosf(XMConvertToRadians(m_lightTheta / 2.0f));
	_context->UpdateSubresource(m_lightConstant.Get(), 0, nullptr, &_lightBuff, 0, 0);
}

//==============================================================================
// 影の作成開始
//==============================================================================
void ShadowMap::Begin()
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	//==============================================================================
	// レンダーターゲットを変更
	//==============================================================================
	auto _rtv = m_renderTexture->GetRenderTargetView();
	auto _dsv = m_depthStencil->GetDepthStencilView();

	// 画面をクリアする
	_context->ClearRenderTargetView(_rtv, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtv, _dsv);

	// ビューポートを設定
	D3D11_VIEWPORT _vp = { 0.0f, 0.0f, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0.0f, 1.0f };
	_context->RSSetViewports(1, &_vp);

	//==============================================================================
	// ライトの行列を計算
	//==============================================================================

	// ライトの方向
	SimpleMath::Vector3 _lightDir =
		SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, 1.0f), m_lightRotate);

	// ビュー行列を作成
	m_lightView = SimpleMath::Matrix::CreateLookAt(
		m_lightPosition,
		m_lightPosition + _lightDir,
		SimpleMath::Vector3::UnitY
	);

	// 射影行列を作成
	m_lightProj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(m_lightTheta), 1.0f, 0.1f, 250.0f);

	//==============================================================================
	// シャドウバッファを更新
	//==============================================================================

	// GPUからのアクセスをロック
	D3D11_MAPPED_SUBRESOURCE _map;
	_context->Map(m_shadowConstant.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &_map);

	// シャドウバッファに計算結果を渡す
	ShadowBuffer _shadowBuff = {};
	_shadowBuff.lightViewProj = XMMatrixTranspose(m_lightView * m_lightProj);
	_shadowBuff.lightPosition = m_lightPosition;
	_shadowBuff.lightDirection = _lightDir;
	_shadowBuff.lightAmbient = SimpleMath::Color(0.3f, 0.3f, 0.3f);

	*static_cast<ShadowBuffer*>(_map.pData) = _shadowBuff;

	// GPUからのアクセスをアンロック
	_context->Unmap(m_shadowConstant.Get(), 0);

	// デプスラムダを格納
	m_depth = [&]() {
		_context->VSSetShader(m_vsDep.Get(), nullptr, 0);
		_context->PSSetShader(m_psDep.Get(), nullptr, 0); };
}

//==============================================================================
// 影作成終了
//==============================================================================
void ShadowMap::End()
{
	//==============================================================================
	// レンダーターゲットとビューポートを元に戻す
	//==============================================================================
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _srvDefault = m_renderTexture->GetShaderResourceView();
	auto _rtvDefault = DX::DeviceResources::GetInstance()->GetRenderTargetView();
	auto _dsvDefault = DX::DeviceResources::GetInstance()->GetDepthStencilView();

	_context->ClearRenderTargetView(_rtvDefault, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(_dsvDefault, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtvDefault, _dsvDefault);
	auto const _vpDefault = DX::DeviceResources::GetInstance()->GetScreenViewport();
	_context->RSSetViewports(1, &_vpDefault);

	//==============================================================================
	// シェーダーの設定
	//==============================================================================
	m_shadow = [&]() {
		// 定数バッファの設定
		ID3D11Buffer* _buffer[] = { m_shadowConstant.Get(), m_lightConstant.Get() };
		_context->VSSetConstantBuffers(1, 1, _buffer);
		_context->PSSetConstantBuffers(1, 2, _buffer);

		// 作成したシャドウマップをリソースとして設定
		_context->PSSetShaderResources(1, 1, &_srvDefault);

		// テクスチャサンプラーの設定
		ID3D11SamplerState* _samplers[] = { m_linearWrap.Get(), m_sampler.Get() };
		_context->PSSetSamplers(0, 2, _samplers);

		// シェーダーの設定
		_context->VSSetShader(m_vs.Get(), nullptr, 0);
		_context->PSSetShader(m_ps.Get(), nullptr, 0); };
}

//==============================================================================
// リリース
//==============================================================================
void ShadowMap::Release()
{
	// リソースの割り当てを解除する
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	ID3D11ShaderResourceView* _nullsrv[] = { nullptr };
	_context->PSSetShaderResources(1, 1, _nullsrv);
}
