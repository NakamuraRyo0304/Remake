/*
 *	@File	AdminCamera.h
 *	@Brief	�J�����̊Ǘ��N���X�B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ADMINCAMERA
#define ADMINCAMERA

// �e�J�����N���X
#include "Game/Common/IGameCamera/IGameCamera.h"

// �q�J�����̃C���N���[�h
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

	// �ړ����x
	static const float MOVE_POS_SPEED;
	// �Ǐ]���x
	static const float FOLLOW_TARGET_SPEED;

public:

	// �A�N�e�B�u��Ԃ��擾
	bool IsActive() const { return is_active; }
	// �A�N�e�B�u��Ԃ�ݒ�
	void SetActive(const bool& flag) { is_active = flag; }

	// �J�����^�C�v���擾
	Type GetType() const { return m_type; }
	// �J�����^�C�v��ݒ�
	void SetType(const Type& cameraType);

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// ���W��ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 pos);

	// �����_���擾
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	// �����_��ݒ�
	void SetTarget(DirectX::SimpleMath::Vector3 target);

	// �r���[�s����擾
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	// �v���W�F�N�V�����s����擾
	DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	// �v���W�F�N�V�����s����쐬
	void SetProjection(const DirectX::SimpleMath::Matrix& proj);

	// �C�[�W���O�̎g�p�ݒ�
	void SetInterpolation(bool flag = true) { is_interpolation = flag; }

public:

	// �R���X�g���N�^
	AdminCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~AdminCamera();
	// �X�V
	void Update();

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
};

#endif // ADMINCAMERA