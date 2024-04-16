/*
 *	@File	EditorCamera.h
 *	@Brief	�G�f�B�^�J�����B
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCAMERA
#define EDITORCAMERA

// �e�J�����N���X
#include "Game/Common/IGameCamera/IGameCamera.h"

class EditorCamera : public IGameCamera
{
public:

	// �R���X�g���N�^
	EditorCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~EditorCamera();
	// �X�V
	void Update() override;

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

	// �ړ����x
	static const float MOVE_SPEED;
	// �ō����x
	static const float MAX_HEIGHT;

private:

	// �J�����̈ʒu���X�V
	void UpdateViewPoint();

private:

	// �r���[�|�C���g���i�[����ϐ�
	ViewPoint m_viewPoint;
	// �ړI�|�C���g
	DirectX::SimpleMath::Vector3 m_viewPosition;
	// �����_�|�C���g
	DirectX::SimpleMath::Vector3 m_viewTarget;

};

#endif // EDITORCAMERA