/*
 *	@File	Lift.h
 *	@Brief	�O��ړ��u���b�N�B
 *	@Date	2024-02-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LIFT
#define LIFT

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Lift : public BaseObject
{
public:

	// �I�t�Z�b�g���擾
	float GetOffset() const { return m_offset; }

	// �R���X�g���N�^
	Lift(DirectX::SimpleMath::Vector3 position);
	// �f�X�g���N�^
	~Lift();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// �ړ���
	float m_offset;

};

#endif // LIFT