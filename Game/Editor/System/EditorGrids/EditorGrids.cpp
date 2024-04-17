/*
 *  @File   EditorGrids.cpp
 *  @Brief  エディタ用グリッド。
 *  @Date   2024-02-20
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "EditorGrids.h"

// エイリアス宣言
using VPC = DirectX::VertexPositionColor;		// プリミティブバッチオプション

// コンストラクタ
EditorGrids::EditorGrids(const int splitX, const int splitZ)
	:
	m_splitX(splitX),
	m_splitZ(splitZ)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// ベーシックエフェクトの作成と設定
	m_basicEffect =	std::make_unique<BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	// プリミティブバッチの作成
	m_gridPrimitive = std::make_unique<PrimitiveBatch<VPC>>(context, 2);
	m_linePrimitive = std::make_unique<PrimitiveBatch<VPC>>(context, 5);

	// インプットレイアウトの設定
	void const* byte;	size_t size;
	m_basicEffect->GetVertexShaderBytecode(&byte, &size);

	// インプットレイアウトの作成
	device->CreateInputLayout(
		VPC::InputElements, VPC::InputElementCount,
		byte, size, m_inputLayout.GetAddressOf()
	);
}

//==============================================================================
// デストラクタ
//==============================================================================
EditorGrids::~EditorGrids()
{
	m_basicEffect.reset();
	m_gridPrimitive.reset();
	m_linePrimitive.reset();
	m_inputLayout.Reset();
}

//==============================================================================
// 描画処理
//==============================================================================
void EditorGrids::Draw(CommonStates& states, const SimpleMath::Matrix world,
	const SimpleMath::Matrix view, const SimpleMath::Matrix proj, const GXMVECTOR color,
	const SimpleMath::Vector3& offset)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 入力アセンブラの設定（インプットレイアウト）
	context->IASetInputLayout(m_inputLayout.Get());

	// 出力マネージャの設定
	context->OMSetBlendState(states.AlphaBlend(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// 行列を設定
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	// 描画開始
	m_gridPrimitive->Begin();

	// 軸と数を計算
	auto axisX = SimpleMath::Vector3::UnitX * static_cast<float>(m_splitX);
	auto axisZ = SimpleMath::Vector3::UnitZ * static_cast<float>(m_splitZ);

	// 垂直線の描画
	for (size_t i = 0; i <= m_splitX; ++i)
	{
		// スケール係数の計算
		float scaleFact = static_cast<float>(i) / static_cast<float>(m_splitX);
		scaleFact = (scaleFact * 1.0f) - 0.5f;

		// スケールベクトルの計算
		SimpleMath::Vector3 scaleVec = (axisX * scaleFact) + offset;

		// 線の始点と終点の座標を計算して描画
		VPC vertex1(scaleVec - (axisZ * 0.5f), color);
		VPC vertex2(scaleVec + (axisZ * 0.5f), color);
		m_gridPrimitive->DrawLine(vertex1, vertex2);
	}

	// 水平線の描画
	for (size_t i = 0; i <= m_splitZ; i++)
	{
		// スケール係数の計算
		float scaleFact = static_cast<float>(i) / static_cast<float>(m_splitZ);
		scaleFact = (scaleFact * 1.0f) - 0.5f;

		// スケールベクトルの計算
		SimpleMath::Vector3 scaleVec = (axisZ * scaleFact) + offset;

		// 線の始点と終点の座標を計算して描画
		VPC vertex1(scaleVec - (axisX * 0.5f), color);
		VPC vertex2(scaleVec + (axisX * 0.5f), color);
		m_gridPrimitive->DrawLine(vertex1, vertex2);
	}

	// 描画終了
	m_gridPrimitive->End();
}

// 線を描画する(スタート --> エンド)
void EditorGrids::DrawLine(CommonStates& states,
	const SimpleMath::Matrix world, const SimpleMath::Matrix view, const SimpleMath::Matrix proj,
	const SimpleMath::Vector3 start, const SimpleMath::Vector3 end, const GXMVECTOR sColor, const GXMVECTOR eColor)
{
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 入力アセンブラの設定（インプットレイアウト）
	context->IASetInputLayout(m_inputLayout.Get());

	// 出力マネージャの設定
	context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// 行列を設定
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(context);

	// 描画開始
	m_linePrimitive->Begin();

	// 始点と終点を設定して描画する
	VPC vertex1(start, sColor);
	VPC vertex2(end, eColor);
	m_linePrimitive->DrawLine(vertex1, vertex2);

	// 描画終了
	m_linePrimitive->End();
}
