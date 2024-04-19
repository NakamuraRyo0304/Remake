/*
 *	@File	Coin.h
 *	@Brief	�R�C���u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef COIN
#define COIN

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Coin : public BaseObject
{
public:

	// �Փ˒ʒm���擾
	bool IsHit() const { return is_hit; }
	// �Փ˒ʒm��ݒ�
	void SetHitFlag(bool isHit) { is_hit = isHit; }

	// �R���X�g���N�^
	Coin(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Coin();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// ��]���x
	static const float ROTATE_SPEED;

private:

	// �Փ˃t���O
	bool is_hit;

};

#endif // COIN