/*
 *	@File	AdminCamera.h
 *	@Brief	�J�����̊Ǘ��N���X�B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ADMINCAMERA
#define ADMINCAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

//==============================================================================
// �q�J�����̃C���N���[�h
//==============================================================================
#include "../FixedPointCamera/FixedPointCamera.h"
#include "../OverHeadCamera/OverHeadCamera.h"

class AdminCamera
{
public:

	// �J�����^�C�v
	enum Type
	{
		FixedPoint,		// ��_�J����
		OverHead,		// ���ՃJ����

		Length,			// �J�����̐�
	};

private:

	// �J�����^�C�v
	Type m_type;

	// �Q�[���J����
	std::unique_ptr<IGameCamera> m_gameCamera;

	// �A�N�e�B�u�t���O
	bool is_active;

	// �E�B���h�E�T�C�Y
	DirectX::SimpleMath::Vector2 m_screenSize;

	// ���W/�����_
	DirectX::SimpleMath::Vector3 m_position, m_target;

	// �r���[�s��/�v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

private:

	// �ړ����x
	static const float MOVE_POS_SPEED;

	// �Ǐ]���x
	static const float FOLLOW_TARGET_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	AdminCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~AdminCamera();

	/// <summary>
	/// �J�����̍X�V
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

public:
	//==============================================================================
	// �擾�E�ݒ�֐�
	//==============================================================================

	/// <summary>
	/// �A�N�e�B�u��Ԃ��擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�A�N�e�B�u��</returns>
	const bool& IsActive() { return is_active; }
	/// <summary>
	/// �A�N�e�B�u��Ԃ�ݒ�
	/// </summary>
	/// <param name="flag">�A�N�e�B�u���</param>
	/// <returns>�Ȃ�</returns>
	void SetActive(const bool& flag) { is_active = flag; }
	/// <summary>
	/// �J�����^�C�v���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�J�����^�C�v</returns>
	const Type& GetType() { return m_type; }
	/// <summary>
	/// �J�����^�C�v��ݒ�
	/// </summary>
	/// <param name="�J�����^�C�v"></param>
	/// <returns>�Ȃ�</returns>
	void SetType(const Type& cameraType);

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�ڐ��̍��W</returns>
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	/// <summary>
	/// �����_���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�����_</returns>
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
	/// <summary>
	/// �r���[�s����擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�r���[�s��</returns>
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	/// <summary>
	/// �v���W�F�N�V�����s����擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�v���W�F�N�V�����s��</returns>
	DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
};

#endif // ADMINCAMERA