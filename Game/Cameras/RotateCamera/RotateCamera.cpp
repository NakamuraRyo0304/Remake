/*
 *	@File	RotateCamera.cpp
 *	@Brief	��]�J�����B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "RotateCamera.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float RotateCamera::ROTATE_RADIUS = 15.0f;	// ��]�͈�
const float RotateCamera::INCREMENT_VALUE = 0.1f;	// ������

//==============================================================================
// �R���X�g���N�^
//==============================================================================
RotateCamera::RotateCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
	, m_value{ 0.0f }			// ���삷��l
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(0.0f, 10.0f, 0.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
RotateCamera::~RotateCamera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void RotateCamera::Update()
{
	auto _key = Keyboard::Get().GetState();

	if (_key.Left) { m_value -= INCREMENT_VALUE; }
	if (_key.Right) { m_value += INCREMENT_VALUE; }

	// ��]�ʂ�ۑ�
	float _x = cosf(m_value) - sinf(m_value);
	float _z = sinf(m_value) + cosf(m_value);
	_x *= ROTATE_RADIUS;
	_z *= ROTATE_RADIUS;

	// ���W�̐ݒ�
	SetPosition(SimpleMath::Vector3(_x, GetPosition().y, _z));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
