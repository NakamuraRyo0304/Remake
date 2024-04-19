/*
 *	@File	Bird_Title.h
 *	@Brief	�^�C�g���ɕ\������g���B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BIRD_TITLE
#define BIRD_TITLE

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Bird_Title : public BaseObject
{
public:

	// �R���X�g���N�^
	Bird_Title();
	// �f�X�g���N�^
	~Bird_Title();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// �X�P�[��
	static const float BIRD_SCALE;

};

#endif // STAGE_TITLE