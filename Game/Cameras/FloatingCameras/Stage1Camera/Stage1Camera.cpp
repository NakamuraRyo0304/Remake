/*
 *	@File	Stage1Camera.cpp
 *	@Brief	�X�e�[�W�P�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage1Camera.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Stage1Camera::Stage1Camera(const SimpleMath::Vector2& screenSize)
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
Stage1Camera::~Stage1Camera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void Stage1Camera::Update()
{
	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
