/*
 *	@File	RayCast.cpp
 *	@Brief	���C���΂��ăX�N���[�����W�����[���h���W�ɕϊ�����B
 *	@Date	2023-05-26
 *  @Author NakamuraRyo
 */

 // �g�p�֐��Q�̎Q�l����
 //-------------------------------------------------------------------------------------//
 //  �܂�؂�
 //  ���̂S�W�@�X�N���[�����W�Ń��[���h��Ԃ̒n�ʂ��w��
 //  http://marupeke296.com/DXG_No48_PointGroundInScreen.html
 //  �F ���J�A�X�N���[�����W�_�ƒn�ʂ̌�_�Z�o�֐����
 //-------------------------------------------------------------------------------------//

#include "pch.h"
#include "RayCast.h"

// �R���X�g���N�^
RayCast::RayCast()
	:
	m_screenSize(),			// �X�N���[���̃T�C�Y
	m_convertPosition()		// ���[���h���W�ɕϊ��������W
{
	auto size = DX::DeviceResources::GetInstance()->GetOutputSize();
	m_screenSize = { static_cast<float>(size.right),static_cast<float>(size.bottom) };
}

// �f�X�g���N�^
RayCast::~RayCast()
{

}

// �X�V
void RayCast::Update()
{
	// ���C���΂��Č�_�����߂�
	m_convertPosition = ShotRay();
}

// ���C���΂��Ēn�ʂƂ̌�_���o��
SimpleMath::Vector3 RayCast::ShotRay()
{
	// �}�E�X���W���擾
	auto ms = Mouse::Get().GetState();

	// �ŋ߁A�ŉ��A���C���`
	SimpleMath::Vector3 nearPos;
	SimpleMath::Vector3 farPos;
	SimpleMath::Vector3 ray;

	// �ŋߋ������X�N���[�����烏�[���h�ɕϊ�
	nearPos = ConvertScreenToWorld(ms.x, ms.y, 0.0f,
		static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y),
		m_view, m_projection);

	// �ŉ��������X�N���[�����烏�[���h�ɕϊ�
	farPos = ConvertScreenToWorld(ms.x, ms.y, 1.0f,
		static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y),
		m_view, m_projection);

	// ���C�̕��������߂�
	ray = farPos - nearPos;
	ray.Normalize();

	// Y���W�ŏ����̏�����
	SimpleMath::Vector3 output = SimpleMath::Vector3::Zero;

	// ���Ƃ̌������N���Ă���ꍇ�͌�_�A�N���Ă��Ȃ��ꍇ�͉����̕ǂƂ̌�_���o��
	if (ray.y <= 0)
	{
		// ���Ƃ̌�_�����߂�
		SimpleMath::Vector3 rayDot = XMVector3Dot(ray, SimpleMath::Vector3(0, 1, 0));
		SimpleMath::Vector3 nearDot = XMVector3Dot(-nearPos, SimpleMath::Vector3(0, 1, 0));
		output = nearPos + (nearDot / rayDot) * ray;

		// Y�Ō�_XZ�������āAY�v�f������
		output.y = 0;
	}
	else
	{
		// �������Ă��Ȃ���΍ŉ������i�����I�Ȗ����j���o��
		output = farPos;
	}

	return output;
}

// ���W�ϊ��@�X�N���[�����W�@���@���[���h���W
SimpleMath::Vector3 RayCast::ConvertScreenToWorld(int mx, int my, float fz,
	int width, int height, SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// �e�s��̋t�s����Z�o
	XMMATRIX reverseView, reverseProj, vp, reverseVp = XMMATRIX::XMMATRIX();

	// �t�s��ɕϊ�
	reverseView = XMMatrixInverse(nullptr, view);
	reverseProj = XMMatrixInverse(nullptr, proj);

	// �r���[�|�[�g��������
	vp = XMMatrixIdentity();

	XMFLOAT4X4 matrix = XMFLOAT4X4::XMFLOAT4X4();

	// �X�P�[���ƃI�t�Z�b�g��ϊ�
	matrix._11 =   width / 2.0f;
	matrix._22 = -height / 2.0f;
	matrix._41 =   width / 2.0f;
	matrix._42 =  height / 2.0f;

	// �r���[�|�[�g�ɍs��ϊ�
	vp += XMLoadFloat4x4(&matrix);

	// �r���[�|�[�g�̋t�s����쐬
	reverseVp = XMMatrixInverse(nullptr,vp);

	// �t�ϊ�
	XMMATRIX reverseMatrix = reverseVp * reverseProj * reverseView;

	XMVECTOR output = XMVector3TransformCoord(
		SimpleMath::Vector3(static_cast<float>(mx), static_cast<float>(my), fz), reverseMatrix);

	return output;
}
