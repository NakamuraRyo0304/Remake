/*
 *	@File	Stage2Camera.cpp
 *	@Brief	�X�e�[�W�Q�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage2Camera.h"

// �R���X�g���N�^
Stage2Camera::Stage2Camera(const SimpleMath::Vector2& screenSize)
	:
	BaseCamera(screenSize)		// ���N���X�̃R���X�g���N�^
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(15.5f, 10.0f, 15.0f));
	SetTarget(SimpleMath::Vector3(15.5f, 5.0f, 7.5f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// �f�X�g���N�^
Stage2Camera::~Stage2Camera()
{
}

// �X�V
void Stage2Camera::Update()
{
	// ���V���Ă��镗�̓���
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
