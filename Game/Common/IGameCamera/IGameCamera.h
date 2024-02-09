/*
 *	@File	IGameCamera.h
 *	@Brief	�J�����̊�b�����B
 *	@Date	2023-11-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMECAMERA
#define IGAMECAMERA

class IGameCamera
{
private:

	// �J�����s��
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_projection;

	// �`��p���W�n
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_target;
	DirectX::SimpleMath::Vector3 m_up;

	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition, m_initialTarget;

	// �X�N���[���T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

private:

	// �J�����̍ŋߋ���
	const float NEAR_PLANE = 0.1f;

	// �J�����̍ŉ�����
	const float FAR_PLANE = 200.0f;

	// �J�����A���O��
	const float ANGLE = 45.0f;


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	IGameCamera(const DirectX::SimpleMath::Vector2& screenSize);
	virtual ~IGameCamera() = default;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Update() = 0;

public:
	// �r���[�s����擾
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	// �r���[�s���ݒ�
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// �v���W�F�N�V�����s����擾
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// ��������擾
	const DirectX::SimpleMath::Vector3& GetUp() { return m_up; }
	// �����_���擾
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	// �����_��ݒ�
	void SetTarget(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	// �����ʒu���擾
	const DirectX::SimpleMath::Vector3& GetInitialPosition() { return m_initialPosition; }
	// �����ʒu��ݒ�
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }
	// ���������_���擾
	const DirectX::SimpleMath::Vector3& GetInitialTarget() { return m_initialTarget; }
	// ���������_��ݒ�
	void SetInitialTarget(const DirectX::SimpleMath::Vector3& target) { m_initialTarget = target; }
	// �E�B���h�E�T�C�Y���擾
	const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_screenSize; }

private:

	/// <summary>
	/// �v���W�F�N�V�������쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateProjection();

};

#endif // IGAMECAMERA