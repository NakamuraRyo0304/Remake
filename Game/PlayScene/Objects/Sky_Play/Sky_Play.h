/*
 *	@File	Sky_Play.h
 *	@Brief	�X�J�C�h�[���I�u�W�F�N�g�B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SKY_PLAY
#define SKY_PLAY

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class Sky_Play : public IGameObject
{
public:

	// �R���X�g���N�^
	Sky_Play();
	// �f�X�g���N�^
	~Sky_Play();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// ��]���x
	static const float ROTATE_SPEED;

};

#endif // SKY_PLAY