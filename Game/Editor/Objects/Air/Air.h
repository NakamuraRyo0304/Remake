/*
 *	@File	Air.h
 *	@Brief	����p�I�u�W�F�N�g�i�G�f�B�^�j�B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef AIR
#define AIR

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class Air : public IGameObject
{
public:

	// �R���X�g���N�^
	Air(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Air();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;
private:

	// �Փ˃t���O
	bool is_hit;

};

#endif // AIR