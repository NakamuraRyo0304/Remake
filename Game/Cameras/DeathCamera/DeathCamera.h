/*
 *	@File	DeathCamera.h
 *	@Brief	���S���J�����B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DEATHCAMERA
#define DEATHCAMERA

// �e�J�����N���X
#include "Game/Common/IGameCamera/IGameCamera.h"

class DeathCamera : public IGameCamera
{
public:

	// �R���X�g���N�^
	DeathCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~DeathCamera();
	// �X�V
	void Update() override;

private:

	// �ړ����x
	static const float MOVE_SPEED;

};

#endif // DEATHCAMERA