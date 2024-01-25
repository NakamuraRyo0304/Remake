/*
 *	@File	NewCamera.h
 *	@Brief	�J�����̐V�K�����N���X�B
 *	@Date	2024-01-20
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef NEWCAMERA
#define NEWCAMERA

class NewCamera
{
private:

	// �s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// �J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// �J�����̒����_
	DirectX::SimpleMath::Vector3 m_targetPosition;

	// �J�����̏����
	DirectX::SimpleMath::Vector3 m_upDirection;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	NewCamera();
	~NewCamera();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="target">�����_</param>
	/// <param name="angle">��p</param>
	/// <param name="aspect">��ʃA�X�y�N�g��</param>
	/// <param name="nearClip">�ł��߂�����</param>
	/// <param name="farClip">�ł���������</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 target,
		float angle,float aspect, float nearClip, float farClip);
};

#endif // NEWCAMERA
