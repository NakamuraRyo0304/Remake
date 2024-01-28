/*
 *	@File	AdminCamera.cpp
 *	@Brief	�J�����̊Ǘ��N���X�B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "AdminCamera.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float AdminCamera::MOVE_POS_SPEED = 0.025f;
const float AdminCamera::FOLLOW_TARGET_SPEED = 0.05f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
AdminCamera::AdminCamera(const SimpleMath::Vector2& screenSize)
	: m_screenSize{ screenSize }
	, m_type{}
	, is_active{ true }
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
AdminCamera::~AdminCamera()
{
	m_gameCamera.reset();
}

//==============================================================================
// �X�V
//==============================================================================
void AdminCamera::Update()
{
	if (m_gameCamera == nullptr) return;

	// �X�V���ăZ�b�g����
	m_gameCamera->Update();

	// ��Ԃ��Ȃ���ړ�����
	m_position = SimpleMath::Vector3::Lerp(m_position, m_gameCamera->GetPosition(), MOVE_POS_SPEED);
	m_target = SimpleMath::Vector3::Lerp(m_target, m_gameCamera->GetTarget(), FOLLOW_TARGET_SPEED);
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, m_gameCamera->GetUp());
}

//==============================================================================
// �J�����̕ύX���˗�
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

	// �v���W�F�N�V�����s����Z�b�g
	m_projection = m_gameCamera->GetProjection();
}
