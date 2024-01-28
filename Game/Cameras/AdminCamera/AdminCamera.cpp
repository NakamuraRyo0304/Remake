/*
 *	@File	AdminCamera.cpp
 *	@Brief	カメラの管理クラス。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "AdminCamera.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float AdminCamera::MOVE_POS_SPEED = 0.025f;
const float AdminCamera::FOLLOW_TARGET_SPEED = 0.05f;

//==============================================================================
// コンストラクタ
//==============================================================================
AdminCamera::AdminCamera(const SimpleMath::Vector2& screenSize)
	: m_screenSize{ screenSize }
	, m_type{}
	, is_active{ true }
{
}

//==============================================================================
// デストラクタ
//==============================================================================
AdminCamera::~AdminCamera()
{
	m_gameCamera.reset();
}

//==============================================================================
// 更新
//==============================================================================
void AdminCamera::Update()
{
	if (m_gameCamera == nullptr) return;

	// 更新してセットする
	m_gameCamera->Update();

	// 補間しながら移動する
	m_position = SimpleMath::Vector3::Lerp(m_position, m_gameCamera->GetPosition(), MOVE_POS_SPEED);
	m_target = SimpleMath::Vector3::Lerp(m_target, m_gameCamera->GetTarget(), FOLLOW_TARGET_SPEED);
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, m_gameCamera->GetUp());
}

//==============================================================================
// カメラの変更を依頼
//==============================================================================
void AdminCamera::SetType(const Type& cameraType)
{
	m_type = cameraType;

	switch (cameraType)
	{
	case Type::Title_FixedPoint:
		m_gameCamera = std::make_unique<FixedPointCamera>(m_screenSize);
		break;
	case Type::Title_OverHead:
		m_gameCamera = std::make_unique<OverHeadCamera>(m_screenSize);
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
	case Type::Editor_Moving:
		m_gameCamera = std::make_unique<EditorCamera>(m_screenSize);
		break;
	default:
		break;
	}

	// プロジェクション行列をセット
	m_projection = m_gameCamera->GetProjection();
}
