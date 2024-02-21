/*
 *  @File   EditorGrids.cpp
 *  @Brief  エディタ用グリッド。
 *  @Date   2024-02-20
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "EditorGrids.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using VPC = DirectX::VertexPositionColor;		// プリミティブバッチオプション

//==============================================================================
// コンストラクタ
//==============================================================================
EditorGrids::EditorGrids(const int splitX, const int splitZ)
	: m_splitX{ splitX }
	, m_splitZ{ splitZ }
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// ベーシックエフェクトの作成と設定
	m_basicEffect =	std::make_unique<BasicEffect>(_device);
	m_basicEffect->SetVertexColorEnabled(true);

	// プリミティブバッチの作成
	m_gridPrimitive = std::make_unique<PrimitiveBatch<VPC>>(_context, 2);
	m_linePrimitive = std::make_unique<PrimitiveBatch<VPC>>(_context, 5);

	// インプットレイアウトの設定
	void const* _byte;	size_t _size;
	m_basicEffect->GetVertexShaderBytecode(&_byte, &_size);

	// インプットレイアウトの作成
	_device->CreateInputLayout(
		VPC::InputElements, VPC::InputElementCount,
		_byte, _size, m_inputLayout.GetAddressOf()
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
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 入力アセンブラの設定（インプットレイアウト）
	_context->IASetInputLayout(m_inputLayout.Get());

	// 出力マネージャの設定
	_context->OMSetBlendState(states.AlphaBlend(), nullptr, 0xFFFFFFFF);
	_context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// 行列を設定
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(_context);

	// 描画開始
	m_gridPrimitive->Begin();

	// 軸と数を計算
	auto _axisX = SimpleMath::Vector3::UnitX * static_cast<float>(m_splitX);
	auto _axisZ = SimpleMath::Vector3::UnitZ * static_cast<float>(m_splitZ);

	// 垂直線の描画
	for (size_t i = 0; i <= m_splitX; ++i)
	{
		// スケール係数の計算
		float _scaleFact = static_cast<float>(i) / static_cast<float>(m_splitX);
		_scaleFact = (_scaleFact * 1.0f) - 0.5f;

		// スケールベクトルの計算
		SimpleMath::Vector3 _scaleVec = (_axisX * _scaleFact) + offset;

		// 線の始点と終点の座標を計算して描画
		VPC _v1(_scaleVec - (_axisZ * 0.5f), color);
		VPC _v2(_scaleVec + (_axisZ * 0.5f), color);
		m_gridPrimitive->DrawLine(_v1, _v2);
	}

	// 水平線の描画
	for (size_t i = 0; i <= m_splitZ; i++)
	{
		// スケール係数の計算
		float _scaleFact = static_cast<float>(i) / static_cast<float>(m_splitZ);
		_scaleFact = (_scaleFact * 1.0f) - 0.5f;

		// スケールベクトルの計算
		SimpleMath::Vector3 _scaleVec = (_axisZ * _scaleFact) + offset;

		// 線の始点と終点の座標を計算して描画
		VPC _v1(_scaleVec - (_axisX * 0.5f), color);
		VPC _v2(_scaleVec + (_axisX * 0.5f), color);
		m_gridPrimitive->DrawLine(_v1, _v2);
	}

	// 描画終了
	m_gridPrimitive->End();
}

//==============================================================================
// 線を描画するスタート ---> エンド
//==============================================================================
void EditorGrids::DrawLine(CommonStates& states,
	const SimpleMath::Matrix world, const SimpleMath::Matrix view, const SimpleMath::Matrix proj,
	const SimpleMath::Vector3 start, const SimpleMath::Vector3 end, const GXMVECTOR sColor, const GXMVECTOR eColor)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 入力アセンブラの設定（インプットレイアウト）
	_context->IASetInputLayout(m_inputLayout.Get());

	// 出力マネージャの設定
	_context->OMSetBlendState(states.Opaque(), nullptr, 0xFFFFFFFF);
	_context->OMSetDepthStencilState(states.DepthDefault(), 0);

	// 行列を設定
	m_basicEffect->SetWorld(world);
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(proj);
	m_basicEffect->Apply(_context);

	// 描画開始
	m_linePrimitive->Begin();

	// 始点と終点を設定して描画する
	VPC _v1(start, sColor);
	VPC _v2(end, eColor);
	m_linePrimitive->DrawLine(_v1, _v2);

	// 描画終了
	m_linePrimitive->End();
}
