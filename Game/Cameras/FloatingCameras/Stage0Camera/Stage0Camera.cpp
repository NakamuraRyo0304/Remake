/*
 *	@File	Stage0Camera.cpp
 *	@Brief	�X�e�[�W�O�i�G�f�B�^�j�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage0Camera.h"

// �R���X�g���N�^
Stage0Camera::Stage0Camera(const SimpleMath::Vector2& screenSize)
	:
	BaseCamera(screenSize)		// ���N���X�̃R���X�g���N�^
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(10.0f, 30.0f, 10.0f));
	SetTarget(SimpleMath::Vector3(10.0f, 0.0f, 0.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// �f�X�g���N�^
Stage0Camera::~Stage0Camera()
{
}

// �X�V
void Stage0Camera::Update()
{
	// ���V���Ă��镗�̓���
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
