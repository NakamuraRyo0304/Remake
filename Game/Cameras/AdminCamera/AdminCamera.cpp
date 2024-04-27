/*
 *	@File	AdminCamera.cpp
 *	@Brief	カメラの管理クラス。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "AdminCamera.h"

// 定数の設定
const float AdminCamera::MOVE_POS_SPEED = 0.025f;
const float AdminCamera::FOLLOW_TARGET_SPEED = 0.05f;

// コンストラクタ
AdminCamera::AdminCamera(const SimpleMath::Vector2& screenSize)
	:
	m_screenSize(screenSize),	// 基底クラスのコンストラクタ
	m_type(),					// カメラタイプ
	is_active(true),			// アクティブフラグ
	is_interpolation(true)		// カメラの補間フラグ
{
}

// デストラクタ
AdminCamera::~AdminCamera()
{
	m_gameCamera.reset();
}

// 更新
void AdminCamera::Update()
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// 更新してセットする
	m_gameCamera->Update();

	// ビュー行列が同じになったら処理をしない
	if (m_view == m_gameCamera->GetView()) return;

	// 補間しながら移動する
	if (is_interpolation)
	{
		m_position = SimpleMath::Vector3::Lerp(m_position, m_gameCamera->GetPosition(), MOVE_POS_SPEED);
		m_target = SimpleMath::Vector3::Lerp(m_target, m_gameCamera->GetTarget(), FOLLOW_TARGET_SPEED);
	}
	// 直接、瞬間的に移動する
	else
	{
		m_position = m_gameCamera->GetPosition();
		m_target = m_gameCamera->GetTarget();
	}
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, m_gameCamera->GetUp());
}

// カメラのタイプを設定
void AdminCamera::SetType(const Type& cameraType)
{
	m_type = cameraType;

	switch (cameraType)
	{
	case Type::Title_FixedPoint:
		m_gameCamera = std::make_unique<FixedPointCamera>(m_screenSize);
		break;
	case Type::Select0_Floating:
		m_gameCamera = std::make_unique<Stage0Camera>(m_screenSize);
		break;
	case Type::Select1_Floating:
		m_gameCamera = std::make_unique<Stage1Camera>(m_screenSize);
		break;
	case Type::Select2_Floating:
		m_gameCamera = std::make_unique<Stage2Camera>(m_screenSize);
		break;
	case Type::Select3_Floating:
		m_gameCamera = std::make_unique<Stage3Camera>(m_screenSize);
		break;
	case Type::Select4_Floating:
		m_gameCamera = std::make_unique<Stage4Camera>(m_screenSize);
		break;
	case Type::Editor_Moving:
		m_gameCamera = std::make_unique<EditorCamera>(m_screenSize);
		break;
	case Type::Death_Following:
		m_gameCamera = std::make_unique<DeathCamera>(m_screenSize);
		break;
	default:
		break;
	}

	// プロジェクション行列をセット
	m_projection = m_gameCamera->GetProjection();
}

// 座標を設定
void AdminCamera::SetPosition(SimpleMath::Vector3 pos)
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// 座標を設定
	m_gameCamera->SetPosition(pos);
}

// 注視点を設定
void AdminCamera::SetTarget(SimpleMath::Vector3 target)
{
	if(UserUtility::IsNull(m_gameCamera.get())) return;

	// ターゲットを設定
	m_gameCamera->SetTarget(target);
}

// プロジェクション行列を作成する
void AdminCamera::SetProjection(const SimpleMath::Matrix& proj)
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// ターゲットを設定
	m_gameCamera->SetProjection(proj);
}
