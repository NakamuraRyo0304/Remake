/*
 *	@File	EditorCamera.h
 *	@Brief	�G�f�B�^�J�����B
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCAMERA
#define EDITORCAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class EditorCamera : public IGameCamera
{
private:

	// ���_�ԍ�
	enum class ViewPoint
	{
		PointFront,		// �O���ʒu
		PointRight,		// �E���ʒu
		PointBack,		// ����ʒu
		PointLeft,		// �����ʒu

		Length,			// �S�v�f��
	};

	// �r���[�|�C���g���i�[����ϐ�
	ViewPoint m_viewPoint;

	// �ړI�|�C���g
	DirectX::SimpleMath::Vector3 m_viewPosition;

	// �����_�|�C���g
	DirectX::SimpleMath::Vector3 m_viewTarget;

private:

	// �ړ����x
	static const float MOVE_SPEED;

	// �ō����x
	static const float MAX_HEIGHT;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	EditorCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~EditorCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;

private:

	/// <summary>
	/// �J�����̈ʒu���X�V
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void UpdateViewPoint();
};

#endif // EDITORCAMERA