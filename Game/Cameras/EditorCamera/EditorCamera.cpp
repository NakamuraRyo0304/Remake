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
const float EditorCamera::MOVE_SPEED = 0.02f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
EditorCamera::EditorCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(0.0f, 5.0f, 12.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
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
    auto _key = Keyboard::Get().GetState();
    auto _forward = UserUtility::GetDirectionVector(GetPosition(), GetTarget());

    if (_key.W)
    {
        SetPosition(GetPosition() + _forward * MOVE_SPEED);
        SetTarget(GetTarget() + _forward * MOVE_SPEED);
    }
    if (_key.S)
    {
        SetPosition(GetPosition() - SimpleMath::Vector3::UnitZ * _forward * MOVE_SPEED);
        SetTarget(GetTarget() - SimpleMath::Vector3::UnitZ * _forward * MOVE_SPEED);
    }
    if (_key.D)
    {
        SetTarget(GetTarget() + SimpleMath::Vector3::UnitX * MOVE_SPEED * 2);
    }
    if (_key.A)
    {
        SetTarget(GetTarget() - SimpleMath::Vector3::UnitX * MOVE_SPEED * 2);
    }

    // �r���[�s����Z�b�g
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
