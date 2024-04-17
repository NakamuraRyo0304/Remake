/*
 *	@File	EditChara.h
 *	@Brief	�v���C���[�i�G�f�B�^�j�B
 *	@Date	2024-02-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITCHARA
#define EDITCHARA

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class EditChara : public IGameObject
{
public:

	// �R���X�g���N�^
	EditChara(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~EditChara();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) final;

};
#endif // EDITCHARA