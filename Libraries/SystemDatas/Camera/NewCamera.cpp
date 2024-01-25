/*
 *	@File	NewCamera.cpp
 *	@Brief	�J�����̐V�K�����N���X�B
 *	@Date	2024-01-20
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "NewCamera.h"

//==============================================================================
// �萔�̏�����
//==============================================================================

//==============================================================================
// �R���X�g���N�^
//==============================================================================
NewCamera::NewCamera()
	: m_view{}					// �r���[�s��
	, m_projection{}			// �v���W�F�N�V�����s��
	, m_position{}				// �ڐ��̈ʒu
	, m_targetPosition{}		// �����_�̈ʒu
	, m_upDirection{}			// �����
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
NewCamera::~NewCamera()
{
}

//==============================================================================
// ����������
//==============================================================================
void NewCamera::Initialize(SimpleMath::Vector3 position, SimpleMath::Vector3 target,
	float angle, float aspect, float nearClip, float farClip)
{
	m_position = position;
	m_targetPosition = target;

	// �J�����̃����Y�̍쐬
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(angle),		// �J�����̉�p
		aspect,							// �A�X�y�N�g��
		nearClip,						// �ŋߋ���
		farClip							// �ŉ�����
	);
}
