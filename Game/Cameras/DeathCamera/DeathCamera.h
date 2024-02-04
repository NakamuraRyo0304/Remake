/*
 *	@File	DeathCamera.h
 *	@Brief	���S���J�����B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DEATHCAMERA
#define DEATHCAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class DeathCamera : public IGameCamera
{
private:

	// �ړ����x
	static const float MOVE_SPEED;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	DeathCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~DeathCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;

};

#endif // DEATHCAMERA