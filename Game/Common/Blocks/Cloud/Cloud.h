/*
 *	@File	Cloud.h
 *	@Brief	�_�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLOUD
#define CLOUD

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class Timer;
class Cloud : public IGameObject
{
public:

	// �Փ˒ʒm
	void SetHitFlag(const bool& isHit) { is_hit = isHit; }

public:

	// �R���X�g���N�^
	Cloud(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Cloud();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// ���쎞��
	static const float LIMIT;

private:

	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;
	// �Փ˃t���O
	bool is_hit;
};

#endif // CLOUD