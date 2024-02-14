/*
 *	@File	FixedPointCamera.cpp
 *	@Brief	��_�J�����B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "FixedPointCamera.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
FixedPointCamera::FixedPointCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(0.0f, 5.0f, 24.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 12.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
FixedPointCamera::~FixedPointCamera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void FixedPointCamera::Update()
{
	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
