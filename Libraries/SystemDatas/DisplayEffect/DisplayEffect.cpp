/*
 *	@File	DisplayEffect.cpp
 *	@Brief	画面効果。
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DisplayEffect.h"

//==============================================================================
// 定数の設定
//==============================================================================
const UINT DisplayEffect::VERTEX_COUNT = 1;	// 頂点数

//==============================================================================
// コンストラクタ
//==============================================================================
DisplayEffect::DisplayEffect(RECT rect)
	: m_size{ rect }					// 画面サイズ
	, m_mode{ DisplayMode::Default }	// 画面効果
	, m_shaders{ nullptr }				// シェーダー
	, m_worldPosition{}					// ワールド行列
	, m_scale{}							// スケール行列
	, m_rotate{}						// 回転行列
{
	auto _pDR = DX::DeviceResources::GetInstance();
	m_renderTexture = std::make_unique<DX::RenderTexture>(_pDR->GetBackBufferFormat());
	m_renderTexture->SetDevice(_pDR->GetD3DDevice());
	m_renderTexture->SetWindow(rect);

	// 初期状態を保存
	m_viewPointer = std::make_unique<ViewPointer>();
	m_viewPointer->pRenderTarget = _pDR->GetRenderTargetView();
	m_viewPointer->pDepthStencil = _pDR->GetDepthStencilView();
}

//==============================================================================
// デストラクタ
//==============================================================================
DisplayEffect::~DisplayEffect()
{
	m_viewPointer.reset();
	m_shaders.reset();
	m_renderTexture->ReleaseDevice();
}

//==============================================================================
// 画面効果を設定する
//==============================================================================
void DisplayEffect::Initialize(const DisplayMode& mode)
{
	m_mode = mode;
	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();
	auto _device = _pDR->GetD3DDevice();

	// シェーダーを作成
	CreateShaders();
	SetDisplayMode(mode);

	// プリミティブバッチを作成
	m_batch = std::make_unique<PrimitiveVertex>(_context);

	// コモンステートを作成
	m_states = std::make_unique<CommonStates>(_device);
}

//==============================================================================
// 画面効果開始
//==============================================================================
void DisplayEffect::Begin()
{
	// 割り当てがなければスキップ
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();
	auto _rtv = m_renderTexture->GetRenderTargetView();

	// 初期状態を保存
	m_viewPointer->pRenderTarget = _pDR->GetRenderTargetView();
	m_viewPointer->pDepthStencil = _pDR->GetDepthStencilView();

	// シェーダーリソースを取得
	m_shaderResouce = m_renderTexture->GetShaderResourceView();

	// レンダーターゲットとデプスステンシルを初期化
	_context->ClearRenderTargetView(_rtv, Colors::White);
	_context->ClearDepthStencilView(m_viewPointer->pDepthStencil, USER_DEPTH_MODE, 1.0f, 0);
	_context->OMSetRenderTargets(1, &_rtv, m_viewPointer->pDepthStencil);
}

//==============================================================================
// 画面効果終了
//==============================================================================
void DisplayEffect::End()
{
	// 割り当てがなければスキップ
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// レンダーターゲットとデプスステンシルを元に戻す
	_context->ClearRenderTargetView(m_viewPointer->pRenderTarget, Colors::CornflowerBlue);
	_context->ClearDepthStencilView(m_viewPointer->pDepthStencil, USER_DEPTH_MODE, 1.0f, 0);
	_context->OMSetRenderTargets(1, &m_viewPointer->pRenderTarget, m_viewPointer->pDepthStencil);
}

//==============================================================================
// シェーダーを作成する
//==============================================================================
void DisplayEffect::CreateShaders()
{
	// シェーダーを作成
	m_shaders = std::make_unique<ShaderPack>();

	// シェーダーファイルの読み込み
	auto _VS = ReadShader(L"Resources/Shaders/DisplayEffects/VGS/DisplayVS.cso");
	auto _GS = ReadShader(L"Resources/Shaders/DisplayEffects/VGS/DisplayGS.cso");
	auto _PS = ReadShader(L"Resources/Shaders/DisplayEffects/Brown/BrownPS.cso");

	// インプットレイアウトの作成
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	_device->CreateInputLayout(&INPUT_LAYOUT[0], static_cast<UINT>(INPUT_LAYOUT.size()),
		_VS.data(), _VS.size(), m_inputLayout.GetAddressOf());

	// 頂点シェーダーの作成
	_device->CreateVertexShader		(_VS.data(), _VS.size(), NULL, m_shaders->VS.ReleaseAndGetAddressOf());
	// ジオメトリシェーダーの作成
	_device->CreateGeometryShader	(_GS.data(), _GS.size(), NULL, m_shaders->GS.ReleaseAndGetAddressOf());
	// ピクセルシェーダーの作成
	_device->CreatePixelShader		(_PS.data(), _PS.size(), NULL, m_shaders->PS.ReleaseAndGetAddressOf());

	// シェーダーにデータを渡すためのコンスタントバッファ生成
	D3D11_BUFFER_DESC _desc;
	ZeroMemory(&_desc, sizeof(_desc));
	_desc.Usage = D3D11_USAGE_DEFAULT;
	_desc.ByteWidth = sizeof(ConstBuffer);
	_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	_desc.CPUAccessFlags = 0;
	_device->CreateBuffer(&_desc, nullptr, &m_buffer);
}

//==============================================================================
// シェーダー読み込み
//==============================================================================
std::vector<uint8_t> DisplayEffect::ReadShader(const wchar_t* path)
{
	return DX::ReadData(path);
}

//==============================================================================
// Start-Endに挟まれたオブジェクトに効果を適用する
//==============================================================================
void DisplayEffect::Apply(SimpleMath::Matrix& view, SimpleMath::Matrix& proj, const bool& flag)
{
	// 割り当てがなければ通常の描画をする
	if (m_mode == DisplayMode::Default) return;

	auto _pDR = DX::DeviceResources::GetInstance();
	auto _context = _pDR->GetD3DDeviceContext();

	// 頂点情報(VERTEX_COUNT)を通常色で初期化
	VertexPositionColorTexture _vertex[VERTEX_COUNT] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3::Zero, Colors::White, SimpleMath::Vector2::Zero),
	};

	// シェーダーに渡すバッファを作成
	ConstBuffer _constBuff;
	if (flag)	// テレビモードならワールド座標に変換する
	{
		for (int i = 0; i < VERTEX_COUNT; i++)
		{
			// ワールド座標をセットする
			_vertex[i] = VertexPositionColorTexture(m_worldPosition, Colors::White, SimpleMath::Vector2::Zero);
		}

		// スケール行列の計算
		SimpleMath::Matrix _world = SimpleMath::Matrix::CreateScale(m_scale);

		// 回転行列の計算
		_world *= SimpleMath::Matrix::CreateRotationX(m_rotate.x);
		_world *= SimpleMath::Matrix::CreateRotationY(m_rotate.y);
		_world *= SimpleMath::Matrix::CreateRotationZ(m_rotate.z);

		// 変換してバッファにセットする
		_constBuff.World = _world.Transpose();
		_constBuff.View = view.Transpose();
		_constBuff.Proj = proj.Transpose();
	}
	_constBuff.Time.x = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// コンスタントバッファの変換
	_context->UpdateSubresource(m_buffer.Get(), 0, nullptr, &_constBuff, 0, 0);

	// シェーダーにコンスタントバッファを渡す
	ID3D11Buffer* _throwBuff[1] = { m_buffer.Get() };
	_context->VSSetConstantBuffers(0, 1, _throwBuff);
	_context->GSSetConstantBuffers(0, 1, _throwBuff);
	_context->PSSetConstantBuffers(0, 1, _throwBuff);

	// 画像用サンプラーの登録
	ID3D11SamplerState* _sampler[1] = { m_states->PointClamp() };
	_context->PSSetSamplers(0, 1, _sampler);

	// 透明判定処理
	_context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込み参照
	_context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングを左周りに設定
	_context->RSSetState(m_states->CullNone());

	// シェーダーを設定
	_context->VSSetShader(m_shaders->VS.Get(), nullptr, 0);
	_context->GSSetShader(m_shaders->GS.Get(), nullptr, 0);
	_context->PSSetShader(m_shaders->PS.Get(), nullptr, 0);

	// リソースを設定
	_context->PSSetShaderResources(0, 1, m_shaderResouce.GetAddressOf());

	// インプットレイアウトを登録
	_context->IASetInputLayout(m_inputLayout.Get());

	// 板ポリゴンを描画
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, _vertex, VERTEX_COUNT);
	m_batch->End();

	// シェーダーの破棄
	_context->VSSetShader(nullptr, nullptr, 0);
	_context->GSSetShader(nullptr, nullptr, 0);
	_context->PSSetShader(nullptr, nullptr, 0);
}

//==============================================================================
// 画面効果を設定
//==============================================================================
void DisplayEffect::SetDisplayMode(const DisplayMode& mode)
{
	m_mode = mode;

	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	std::vector<uint8_t> _shader;

	switch (mode)
	{
	case DisplayMode::Default:
		return;
	case DisplayMode::BrownTVEffect:
		_shader = ReadShader(L"Resources/Shaders/DisplayEffects/Brown/BrownPS.cso");
		break;
	case DisplayMode::MonochromeEffect:
		_shader = ReadShader(L"Resources/Shaders/DisplayEffects/Monochrome/MonochroPS.cso");
		break;
	default:
		break;
	}

	// シェーダーを作成
	_device->CreatePixelShader(_shader.data(), _shader.size(), NULL, m_shaders->PS.ReleaseAndGetAddressOf());
}
