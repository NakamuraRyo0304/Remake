/*
 *	@File	Spike.h
 *	@Brief	���I�u�W�F�N�g(�G)�B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SPIKE
#define SPIKE

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Spike : public BaseObject
{
public:

	// �Փ˒ʒm���擾
	bool IsHitFlag() const { return is_hit; }
	// �Փ˒ʒm
	void SetHitFlag(bool isHit) { is_hit = isHit; }

	// �R���X�g���N�^
	Spike(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Spike();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// �ߐH��]���x
	static const float EATING_SPEED;

private:

	// �Փ˃t���O
	bool is_hit;
};

#endif // SPIKE