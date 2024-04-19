/*
 *	@File	Goal.h
 *	@Brief	�S�[���I�u�W�F�N�g�B
 *	@Date	2024-02-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GOAL
#define GOAL

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Goal : public BaseObject
{
public:

	// �Փ˃t���O��ON�ɂ���(�S�[������͂P�x�̂���ON�̂�)
	void OnHitFlag() { is_hit = true; }
	// �t���O�擾
	bool IsHitFlag() const { return is_hit; }

	// �R���X�g���N�^
	Goal(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Goal();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// �Փ˃t���O
	bool is_hit;

};

#endif // GOAL