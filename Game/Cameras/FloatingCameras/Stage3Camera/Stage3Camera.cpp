/*
 *	@File	Stage3Camera.cpp
 *	@Brief	�X�e�[�W�R�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage3Camera.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Stage3Camera::Stage3Camera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(0.0f, 30.0f, 0.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Stage3Camera::~Stage3Camera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void Stage3Camera::Update()
{
	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
