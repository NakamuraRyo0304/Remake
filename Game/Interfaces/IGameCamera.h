/*
 *	@File	IGameCamera.h
 *	@Brief	�J�����̊�b�����B
 *	@Date	2023-11-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMECAMERA
#define IGAMECAMERA

class IGameCamera
{
public:

	// �f�X�g���N�^
	virtual ~IGameCamera() = default;
	// �X�V
	virtual void Update() = 0;

};

#endif // IGAMECAMERA