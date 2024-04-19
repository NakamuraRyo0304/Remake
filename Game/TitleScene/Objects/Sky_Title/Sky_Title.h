/*
 *	@File	Sky_Title.h
 *	@Brief	�X�J�C�h�[���I�u�W�F�N�g�B
 *	@Date	2023-12-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SKY_TITLE
#define SKY_TITLE

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Sky_Title : public BaseObject
{
public:

	// �R���X�g���N�^
	Sky_Title();
	// �f�X�g���N�^
	~Sky_Title();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

};

#endif // SKY_TITLE