/*
 *	@File	OverHeadCamera.cpp
 *	@Brief	���ՃJ�����B
 *	@Date	2023-12-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "OverHeadCamera.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float OverHeadCamera::AXIS_Y_WIDTH = 3.0f;	// Y���ړ�

//==============================================================================
// �R���X�g���N�^
//==============================================================================
OverHeadCamera::OverHeadCamera(const SimpleMath::Vector2& screenSize)
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
OverHeadCamera::~OverHeadCamera()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void OverHeadCamera::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ���W���Z�b�g
	SetPosition(SimpleMath::Vector3(
		GetPosition().x,
		GetInitialPosition().y + sinf(_timer) * AXIS_Y_WIDTH,
		GetPosition().z)
	);

	// �r���[�s����Z�b�g
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
