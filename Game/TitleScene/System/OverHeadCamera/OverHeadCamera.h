/*
 *	@File	OverHeadCamera.h
 *	@Brief	���ՃJ�����B
 *	@Date	2023-12-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef OVERHEADCAMERA
#define OVERHEADCAMERA

//==============================================================================
// �e�J�����N���X
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class OverHeadCamera : public IGameCamera
{
private:

	// �㉺�ړ��̕�
	static const float AXIS_Y_WIDTH;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="screenSize">�X�N���[���T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	OverHeadCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~OverHeadCamera();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
};

#endif // OVERHEADCAMERA