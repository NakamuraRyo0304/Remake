/*
 *  @File   Iceberg.h
 *  @Brief  �X�R�B
 *  @Date   2024-02-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ICEBERG
#define ICEBERG

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Iceberg : public BaseObject
{
public:

	// �R���X�g���N�^
	Iceberg(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	// �f�X�g���N�^
	~Iceberg();
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

#endif // ICEBERG