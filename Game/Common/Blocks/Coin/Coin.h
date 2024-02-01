/*
 *	@File	Coin.h
 *	@Brief	�R�C���u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef COIN
#define COIN

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Coin : public IGameObject
{
private:

	// �Փ˃t���O
	bool is_hit;

	// �A�N�e�B�u�t���O
	bool is_active;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	/// <returns>�Ȃ�</returns>
	Coin(DirectX::SimpleMath::Vector3 position);
	~Coin();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) override;

public:

	// �A�N�e�B�u�t���O���擾
	bool IsActive() { return is_active; }
	// �A�N�e�B�u�t���O��؂�ւ���
	void SetActive(const bool flag) { is_active = flag; }

	// �Փ˒ʒm
	void SetHitFlag(bool isHit) { is_hit = isHit; }

};

#endif // COIN