/*
 *	@File	Stage1Camera.cpp
 *	@Brief	�X�e�[�W�P�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage1Camera.h"

// �R���X�g���N�^
Stage1Camera::Stage1Camera(const SimpleMath::Vector2& screenSize)
	:
	IGameCamera(screenSize)			// ���N���X
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(3.5f, 10.0f, 15.0f));
	SetTarget(SimpleMath::Vector3(3.5f, 5.0f, 7.5f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// �f�X�g���N�^
Stage1Camera::~Stage1Camera()
{
}

// �X�V
void Stage1Camera::Update()
{
	// ���V���Ă��镗�̓���
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
