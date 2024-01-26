/*
 *	@File	RotateCamera.h
 *	@Brief	��]�J�����B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ROTATECAMERA
#define ROTATECAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class RotateCamera : public IGameCamera
{
private:

	// ���삷���]��
	float m_value;

private:

	// ��]�͈�
	static const float ROTATE_RADIUS;

	// ������
	static const float INCREMENT_VALUE;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	RotateCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~RotateCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // ROTATECAMERA