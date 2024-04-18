/*
 *	@File	IGameCamera.cpp
 *	@Brief	�J�����̊�b�����B
 *	@Date	2023-11-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "IGameCamera.h"

// �R���X�g���N�^
IGameCamera::IGameCamera(const SimpleMath::Vector2& screenSize)
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

// �v���W�F�N�V�����s����쐬
void IGameCamera::CreateProjection()
{
	// ��p
	float fieldOfView = XMConvertToRadians(ANGLE);

	// ��ʏc����
	float aspect = m_screenSize.x / m_screenSize.y;

	// �J�����̃����Y�̍쐬
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fieldOfView,		// �J�����̉�p
		aspect,				// �A�X�y�N�g��
		NEAR_PLANE,			// �ŋߋ���
		FAR_PLANE			// �ŉ�����
	);
}
