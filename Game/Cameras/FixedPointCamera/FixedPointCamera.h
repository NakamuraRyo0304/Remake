/*
 *	@File	FixedPointCamera.h
 *	@Brief	��_�J�����B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FIXEDPOINTCAMERA
#define FIXEDPOINTCAMERA

// �e�J�����N���X
#include "Game/Common/IGameCamera/IGameCamera.h"

class FixedPointCamera : public IGameCamera
{
public:

	// �R���X�g���N�^
	FixedPointCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// �f�X�g���N�^
	~FixedPointCamera();
	// �X�V
	void Update() override;
};

#endif // FIXEDPOINTCAMERA