/*
 *	@File	AdminCamera.cpp
 *	@Brief	�J�����̊Ǘ��N���X�B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "AdminCamera.h"

// �萔�̐ݒ�
const float AdminCamera::MOVE_POS_SPEED = 0.025f;
const float AdminCamera::FOLLOW_TARGET_SPEED = 0.05f;

// �R���X�g���N�^
AdminCamera::AdminCamera(const SimpleMath::Vector2& screenSize)
	:
	m_screenSize(screenSize),	// ���N���X�̃R���X�g���N�^
	m_type(),					// �J�����^�C�v
	is_active(true),			// �A�N�e�B�u�t���O
	is_interpolation(true)		// �J�����̕�ԃt���O
{
}

// �f�X�g���N�^
AdminCamera::~AdminCamera()
{
	m_gameCamera.reset();
}

// �X�V
void AdminCamera::Update()
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// �X�V���ăZ�b�g����
	m_gameCamera->Update();

	// �r���[�s�񂪓����ɂȂ����珈�������Ȃ�
	if (m_view == m_gameCamera->GetView()) return;

	// ��Ԃ��Ȃ���ړ�����
	if (is_interpolation)
	{
		m_position = SimpleMath::Vector3::Lerp(m_position, m_gameCamera->GetPosition(), MOVE_POS_SPEED);
		m_target = SimpleMath::Vector3::Lerp(m_target, m_gameCamera->GetTarget(), FOLLOW_TARGET_SPEED);
	}
	// ���ځA�u�ԓI�Ɉړ�����
	else
	{
		m_position = m_gameCamera->GetPosition();
		m_target = m_gameCamera->GetTarget();
	}
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, m_gameCamera->GetUp());
}

// �J�����̃^�C�v��ݒ�
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

	// �v���W�F�N�V�����s����Z�b�g
	m_projection = m_gameCamera->GetProjection();
}

// ���W��ݒ�
void AdminCamera::SetPosition(SimpleMath::Vector3 pos)
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// ���W��ݒ�
	m_gameCamera->SetPosition(pos);
}

// �����_��ݒ�
void AdminCamera::SetTarget(SimpleMath::Vector3 target)
{
	if(UserUtility::IsNull(m_gameCamera.get())) return;

	// �^�[�Q�b�g��ݒ�
	m_gameCamera->SetTarget(target);
}

// �v���W�F�N�V�����s����쐬����
void AdminCamera::SetProjection(const SimpleMath::Matrix& proj)
{
	if (UserUtility::IsNull(m_gameCamera.get())) return;

	// �^�[�Q�b�g��ݒ�
	m_gameCamera->SetProjection(proj);
}
