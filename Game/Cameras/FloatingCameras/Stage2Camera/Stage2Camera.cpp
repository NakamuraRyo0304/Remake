/*
 *	@File	Stage2Camera.cpp
 *	@Brief	�X�e�[�W�Q�̃Z���N�g�J�����B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage2Camera.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Stage2Camera::Stage2Camera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// ���W�ƒ����_���Z�b�g
	SetPosition(SimpleMath::Vector3(5.0f, 25.0f, 20.0f));
	SetTarget(SimpleMath::Vector3(5.0f, 0.0f, 0.0f));
	// ������Ԃ�ێ�
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Stage2Camera::~Stage2Camera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void Stage2Camera::Update()
{
	// ���V���Ă��镗�̓���
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(_timer));

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
