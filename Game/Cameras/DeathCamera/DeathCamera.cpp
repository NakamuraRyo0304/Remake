/*
 *	@File	DeathCamera.cpp
 *	@Brief	���S���J�����B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "DeathCamera.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================

//==============================================================================
// �R���X�g���N�^
//==============================================================================
DeathCamera::DeathCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(0.0f, -5.0f, 0.0f));
	SetTarget(SimpleMath::Vector3::Zero);
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
DeathCamera::~DeathCamera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void DeathCamera::Update()
{
    // �r���[�s����Z�b�g
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}