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
#include "../FloatingCameras/Stage0Camera/Stage0Camera.h"
#include "../FloatingCameras/Stage1Camera/Stage1Camera.h"
#include "../FloatingCameras/Stage2Camera/Stage2Camera.h"
#include "../FloatingCameras/Stage3Camera/Stage3Camera.h"
#include "../FloatingCameras/Stage4Camera/Stage4Camera.h"
#include "../EditorCamera/EditorCamera.h"
#include "../DeathCamera/DeathCamera.h"

class AdminCamera
{
public:

	// �J�����^�C�v
	enum Type
	{
		Title_FixedPoint,		// ��_�J����
		Select0_Floating,		// �X�e�[�W�O�i�G�f�B�^�j�̒�_�J����
		Select1_Floating,		// �X�e�[�W�P�̒�_�J����
		Select2_Floating,		// �X�e�[�W�Q�̒�_�J����
		Select3_Floating,		// �X�e�[�W�R�̒�_�J����
		Select4_Floating,		// �X�e�[�W�S�̒�_�J����
		Editor_Moving,			// �G�f�B�^���̃t���[�ړ��J����
		Death_Following,		// ���S���̃J����

		Length,					// �J�����̐�
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

	// ��ԃt���O
	bool is_interpolation;

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
	/// ���W��ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <returns>�Ȃ�</returns>
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	/// <summary>
	/// �����_���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�����_</returns>
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
	/// <summary>
	/// �����_��ݒ�
	/// </summary>
	/// <param name="target">�����_</param>
	/// <returns>�Ȃ�</returns>
	void SetTarget(DirectX::SimpleMath::Vector3 target);
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
	/// <summary>
	/// �C�[�W���O�̎g�p�ݒ�
	/// </summary>
	/// <param name="flag">ON�Ő��`�⊮</param>
	/// <returns>�Ȃ�</returns>
	void SetInterpolation(bool flag = true) { is_interpolation = flag; }
};

#endif // ADMINCAMERA