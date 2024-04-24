/*
 *	@File	IGameObject.h
 *	@Brief	�Q�[���I�u�W�F�N�g�̃C���^�[�t�F�[�X�B
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

// �I�u�W�F�N�g�̃X�e�[�^�X
#include "StatesList.h"

class IGameObject
{
public:

	// �f�X�g���N�^
	virtual ~IGameObject() = default;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

};

#endif // IGAMEOBJECT