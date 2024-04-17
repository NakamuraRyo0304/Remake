/*
 *	@File	EditorCamera.cpp
 *	@Brief	エディタカメラ。
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "EditorCamera.h"

// 定数の設定
const float EditorCamera::MOVE_SPEED = 0.1f;	// 移動速度
const float EditorCamera::MAX_HEIGHT = 35.0f;	// 最大高度

// エイリアス宣言
using KeyCode = Keyboard::Keys;					// キーコード

// コンストラクタ
EditorCamera::EditorCamera(const SimpleMath::Vector2& screenSize)
	:
	IGameCamera(screenSize),					// 基底クラス
    m_viewPoint(ViewPoint::PointFront),		    // デフォルトは前方位置
	m_viewPosition(),							// 目的位置
	m_viewTarget()								// 目的注視点
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(4.5f, 12.0f, 10.0f));
	SetTarget(SimpleMath::Vector3(4.5f, 0.0f, 5.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
	// 初期位置を設定
	m_viewPosition = GetInitialPosition();
	m_viewTarget = GetInitialTarget();
}

// デストラクタ
EditorCamera::~EditorCamera()
{
}

// 更新
void EditorCamera::Update()
{
	auto input = Input::GetInstance();
	auto key = Keyboard::Get().GetState();

	// カメラ切り替え
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::D))
		UserUtility::Increment(&m_viewPoint);
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::A))
		UserUtility::Decrement(&m_viewPoint);
	if (key.W)
		m_viewPosition.y += MOVE_SPEED;
	if (key.S)
		m_viewPosition.y -= MOVE_SPEED;

	// ループクランプする
	m_viewPoint = UserUtility::LoopClamp(m_viewPoint, ViewPoint::PointFront, ViewPoint::PointLeft);
	// 高度をクランプする
	m_viewPosition.y = UserUtility::Clamp(m_viewPosition.y, m_viewPosition.y, MAX_HEIGHT);

	// ビューの位置を更新
	UpdateViewPoint();

	// 座標を設定
	SetPosition(UserUtility::Lerp(GetPosition(), m_viewPosition, MOVE_SPEED));
	// 注視点を設定
	SetTarget(UserUtility::Lerp(GetTarget(), m_viewTarget, MOVE_SPEED));
    // ビュー行列をセット
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}

// ビューの位置を更新
void EditorCamera::UpdateViewPoint()
{
	switch(m_viewPoint)
	{
	case ViewPoint::PointFront:
		m_viewPosition = SimpleMath::Vector3(4.5f, m_viewPosition.y, 13.5f);
		m_viewTarget = SimpleMath::Vector3(4.5f, 0.0f, 5.0f);
		break;
	case ViewPoint::PointRight:
		m_viewPosition = SimpleMath::Vector3(13.5f, m_viewPosition.y, 4.5f);
		m_viewTarget = SimpleMath::Vector3(5.0f, 0.0f, 4.5f);
		break;
	case ViewPoint::PointBack:
		m_viewPosition = SimpleMath::Vector3(4.5f, m_viewPosition.y, -5.0f);
		m_viewTarget = SimpleMath::Vector3(4.5f, 0.0f, 4.5f);
		break;
	case ViewPoint::PointLeft:
		m_viewPosition = SimpleMath::Vector3(-4.5f, m_viewPosition.y, 4.5f);
		m_viewTarget = SimpleMath::Vector3(4.5f, 0.0f, 4.5f);
		break;
	default:
		break;
	}
}
