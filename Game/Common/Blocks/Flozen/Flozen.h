/*
 *	@File	Flozen.h
 *	@Brief	�X�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLOZEN
#define FLOZEN

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Flozen : public BaseObject
{
public:

	// �R���X�g���N�^
	Flozen(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Flozen();

	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

};

#endif // FLOZEN