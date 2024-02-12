/*
 *	@File	Stage4Camera.cpp
 *	@Brief	�X�e�[�W�S�̃Z���N�g�J�����B
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage4Camera.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Stage4Camera::Stage4Camera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(3.5f, 10.0f, 5.5f));
	SetTarget(SimpleMath::Vector3(3.5f, 5.0f, -2.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Stage4Camera::~Stage4Camera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void Stage4Camera::Update()
{
	// ���V���Ă��镗�̓���
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(_timer));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
