/*
 *  @File   DrawPath.cpp
 *  @Brief  パス描画クラス。
 *  @Date   2024-04-10
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawPath.h"

//==============================================================================
// コンストラクタ
//==============================================================================
DrawPath::DrawPath(float width)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	void const* _byte;	size_t _size;

	// ベーシックエフェクトの作成と設定
	m_basicEffect = std::make_unique<BasicEffect>(_device);
	m_basicEffect->SetVertexColorEnabled(true);
	m_basicEffect->GetVertexShaderBytecode(&_byte, &_size);

	// プリミティブの作成
	m_primitive = std::make_unique<PrimitiveBatch<VertexPositionColor>>(_context, static_cast<size_t>(width));

	// インプットレイアウトの作成
	_device->CreateInputLayout(VertexPositionColor::InputElements, VertexPositionColor::InputElementCount,
		_byte, _size, m_inputLayout.GetAddressOf());
}

//==============================================================================
// デストラクタ
//==============================================================================
DrawPath::~DrawPath()
{
	m_basicEffect.reset();
	m_primitive.reset();
	m_inputLayout.Reset();
}

//==============================================================================
// 描画関数
//==============================================================================
void DrawPath::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj)
{
	// 入力アセンブラの設定（インプットレイアウト）
	context->IASetInputLayout(m_inputLayout.Get());

	// 出力マネージャの設定
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// 行列を設定
	m_basicEffect->SetWorld(SimpleMath::Matrix::Identity);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	// 描画開始
	m_primitive->Begin();

	// 始点と終点を設定して描画する
	VertexPositionColor _v1(SimpleMath::Vector3(0,0,0), Colors::Red);
	VertexPositionColor _v2(SimpleMath::Vector3(10, 10, 0), Colors::Red);
	m_primitive->DrawLine(_v1, _v2);

	// 描画終了
	m_primitive->End();
}
