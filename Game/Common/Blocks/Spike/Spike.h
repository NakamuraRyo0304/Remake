/*
 *	@File	Spike.h
 *	@Brief	���I�u�W�F�N�g(�G)�B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SPIKE
#define SPIKE

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Spike : public IGameObject
{
private:

	// �Փ˃t���O
	bool is_hit;

	// �A�N�e�B�u�t���O
	bool is_active;

private:

	// �ߐH��]���x
	static const float EATING_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	/// <returns>�Ȃ�</returns>
	Spike(DirectX::SimpleMath::Vector3 position);
	~Spike();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="context">�R���e�L�X�g</param>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <param name="wireframe">���C���[�t���[��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

public:

	// �A�N�e�B�u�t���O���擾
	bool IsActive() { return is_active; }
	// �A�N�e�B�u�t���O��؂�ւ���
	void SetActive(const bool flag) { is_active = flag; }

	// �Փ˒ʒm���擾
	bool IsHitFlag() { return is_hit; }
	// �Փ˒ʒm
	void SetHitFlag(bool isHit) { is_hit = isHit; }

};

#endif // SPIKE