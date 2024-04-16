/*
 *  @File   Island.h
 *  @Brief  �Ǔ��B
 *  @Date   2024-02-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISLAND
#define ISLAND

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class Island : public IGameObject
{
public:

	// �R���X�g���N�^
	Island(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	// �f�X�g���N�^
	~Island();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;
private:

	// ��]��
	float m_rotation;
	// ��]���x
	float m_speed;

};

#endif // ISLAND