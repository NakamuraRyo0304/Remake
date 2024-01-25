/*
 *	@File	NewCamera.cpp
 *	@Brief	カメラの新規改造クラス。
 *	@Date	2024-01-20
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "NewCamera.h"

//==============================================================================
// 定数の初期化
//==============================================================================

//==============================================================================
// コンストラクタ
//==============================================================================
NewCamera::NewCamera()
	: m_view{}					// ビュー行列
	, m_projection{}			// プロジェクション行列
	, m_position{}				// 目線の位置
	, m_targetPosition{}		// 注視点の位置
	, m_upDirection{}			// 上方向
{
}

//==============================================================================
// デストラクタ
//==============================================================================
NewCamera::~NewCamera()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void NewCamera::Initialize(SimpleMath::Vector3 position, SimpleMath::Vector3 target,
	float angle, float aspect, float nearClip, float farClip)
{
	m_position = position;
	m_targetPosition = target;

	// カメラのレンズの作成
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(angle),		// カメラの画角
		aspect,							// アスペクト比
		nearClip,						// 最近距離
		farClip							// 最遠距離
	);
}
