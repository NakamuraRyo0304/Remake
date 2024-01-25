/*
 *	@File	FixedPointCamera.h
 *	@Brief	��_�J�����B
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FIXEDPOINTCAMERA
#define FIXEDPOINTCAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class FixedPointCamera : public IGameCamera
{
private:

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	FixedPointCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~FixedPointCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // FIXEDPOINTCAMERA