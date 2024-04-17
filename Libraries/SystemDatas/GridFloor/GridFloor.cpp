/*
 *	@File	GridFloor.cpp
 *	@Brief	デバッグ用グリッド。
 *	@Date	2021-02-09
 *  @Author T.Matsui
 *  @Editor NakamuraRyo
 */

#include "pch.h"
#include "GridFloor.h"

 // コンストラクタ
Debug::GridFloor::GridFloor(const int divsX, const int divsY)
	:
	m_divsX(divsX),
	m_divsY(divsY),
	m_sizeX(),
	m_sizeY()
{
	auto pDR = DX::DeviceResources::GetInstance();

	// エフェクトの生成
	m_basicEffect =
		std::make_unique<BasicEffect>(pDR->GetD3DDevice());

	// 頂点カラーの設定
	m_basicEffect->SetVertexColorEnabled(true);

	// プリミティブバッチの生成
	m_primitiveBatch =
		std::make_unique<PrimitiveBatch<VertexPositionColor>>(pDR->GetD3DDeviceContext());

	// インプットレイアウトの設定
	void const* byte;
	size_t size;
	m_basicEffect->GetVertexShaderBytecode(&byte, &size);
	pDR->GetD3DDevice()->CreateInputLayout(
		VertexPositionColor::InputElements, VertexPositionColor::InputElementCount,
		byte, size, m_inputLayout.GetAddressOf());
}

// デストラクタ
Debug::GridFloor::~GridFloor()
{
}

// 描画
void Debug::GridFloor::Draw(CommonStates& states, const SimpleMath::Matrix view, const SimpleMath::Matrix proj, const GXMVECTOR color)
{
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	context->IASetInputLayout(m_inputLayout.Get());
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states.DepthDefault(), 0);

	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	m_primitiveBatch->Begin();

	const XMVECTORF32 axisX = { (float)m_divsX, 0.0f, 0.0f };
	const XMVECTORF32 axisY = { 0.0f, 0.0f, (float)m_divsY };

	size_t divsX = std::max<size_t>(1, m_divsX);
	FXMVECTOR origin = g_XMZero;
	// 垂直線
	for (size_t i = 0; i <= divsX; ++i)
	{
		float scaleFac = float(i) / float(divsX);
		scaleFac = (scaleFac * 1.0f) - 0.5f;
		XMVECTOR scaleVec = XMVectorScale(axisX, scaleFac);
		scaleVec = XMVectorAdd(scaleVec, origin);

		VertexPositionColor vertex1(XMVectorSubtract(scaleVec, axisY * 0.5f), color);
		VertexPositionColor vertex2(XMVectorAdd(scaleVec, axisY * 0.5f), color);
		m_primitiveBatch->DrawLine(vertex1, vertex2);
	}
	// 水平線
	size_t divsY = std::max<size_t>(1, m_divsY);
	for (size_t i = 0; i <= divsY; i++)
	{
		float scaleFac = float(i) / float(divsY);
		scaleFac = (scaleFac * 1.0f) - 0.5f;
		XMVECTOR scaleVec = XMVectorScale(axisY, scaleFac);
		scaleVec = XMVectorAdd(scaleVec, origin);

		VertexPositionColor vertex1(XMVectorSubtract(scaleVec, axisX * 0.5f), color);
		VertexPositionColor vertex2(XMVectorAdd(scaleVec, axisX * 0.5f), color);
		m_primitiveBatch->DrawLine(vertex1, vertex2);
	}

	m_primitiveBatch->End();
}
