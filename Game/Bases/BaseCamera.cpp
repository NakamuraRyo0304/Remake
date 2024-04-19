/*
 *  @File   BaseCamera.cpp
 *  @Brief  �J�����̊��N���X�B
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "BaseCamera.h"

// �R���X�g���N�^
BaseCamera::BaseCamera(const SimpleMath::Vector2& screenSize)
	:
	m_view(),											// �r���[�s��
	m_projection(),										// �v���W�F�N�V�����s��
	m_position(SimpleMath::Vector3::Zero),				// �J�������W
	m_target(SimpleMath::Vector3::Zero),				// �����_
	m_up(SimpleMath::Vector3::Up),						// �����
	m_initialPosition(SimpleMath::Vector3::Zero),		// �����ʒu��ݒ�
	m_initialTarget(SimpleMath::Vector3::Zero),			// ���������_��ݒ�
	m_screenSize(screenSize)							// �X�N���[���T�C�Y
{
	CreateProjection();
}

// �f�X�g���N�^
BaseCamera::~BaseCamera()
{
}

// �v���W�F�N�V�����s����쐬
void BaseCamera::CreateProjection()
{
	// ��p
	float fieldOfView = XMConvertToRadians(ANGLE);

	// �A�X�y�N�g��
	float aspect = m_screenSize.x / m_screenSize.y;

	// �J�����̃����Y�̍쐬
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fieldOfView,		// �J�����̉�p
		aspect,				// �A�X�y�N�g��
		NEAR_PLANE,			// �ŋߋ���
		FAR_PLANE			// �ŉ�����
	);
}
