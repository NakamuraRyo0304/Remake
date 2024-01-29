/*
 *	@File	EditorCamera.cpp
 *	@Brief	�G�f�B�^�J�����B
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "EditorCamera.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float EditorCamera::MOVE_SPEED = 0.1f;

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;			// �L�[�R�[�h

//==============================================================================
// �R���X�g���N�^
//==============================================================================
EditorCamera::EditorCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
    , m_viewPoint{ ViewPoint::PointFront }      // �f�t�H���g�͑O���ʒu
	, m_viewPosition{}							// �ړI�ʒu
	, m_viewTarget{}							// �ړI�����_
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(4.5f, 12.0f, 10.0f));
	SetTarget(SimpleMath::Vector3(4.5f, 0.0f, 5.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());

	// �����ʒu��ݒ�
	m_viewPosition = GetInitialPosition();
	m_viewTarget = GetInitialTarget();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
EditorCamera::~EditorCamera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void EditorCamera::Update()
{
	auto _input = Input::GetInstance();
	auto _key = Keyboard::Get().GetState();

	// �J�����؂�ւ�
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::D))
		UserUtility::Increment(&m_viewPoint);
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::A))
		UserUtility::Decrement(&m_viewPoint);
	if (_key.W)
		m_viewPosition.y += MOVE_SPEED;
	if (_key.S)
		m_viewPosition.y -= MOVE_SPEED;

	// ���[�v�N�����v����
	m_viewPoint = UserUtility::LoopClamp(m_viewPoint, ViewPoint::PointFront, ViewPoint::PointUp);

	// �r���[�̈ʒu���X�V
	UpdateViewPoint();

	// ���W��ݒ�
	SetPosition(UserUtility::Lerp(GetPosition(), m_viewPosition, MOVE_SPEED));

	// �����_��ݒ�
	SetTarget(UserUtility::Lerp(GetTarget(), m_viewTarget, MOVE_SPEED));

    // �r���[�s����Z�b�g
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}

//==============================================================================
// �r���[�̈ʒu���X�V����
//==============================================================================
void EditorCamera::UpdateViewPoint()
{
	switch(m_viewPoint)
	{
	case ViewPoint::PointFront:
		m_viewPosition = SimpleMath::Vector3(4.5f, m_viewPosition.y, 10.0f);
		m_viewTarget = SimpleMath::Vector3(4.5f, 0.0f, 5.0f);
		break;
	case ViewPoint::PointRight:
		m_viewPosition = SimpleMath::Vector3(10.0f, m_viewPosition.y, 4.5f);
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
	case ViewPoint::PointUp:
		m_viewPosition = GetInitialPosition() + SimpleMath::Vector3::UnitY * MOVE_SPEED;
		m_viewTarget = GetInitialTarget();
	default:
		break;
	}
}