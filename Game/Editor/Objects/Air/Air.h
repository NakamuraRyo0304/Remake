/*
 *	@File	Air.h
 *	@Brief	����p�I�u�W�F�N�g�i�G�f�B�^�j�B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef AIR
#define AIR

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Air : public IGameObject
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
	Air(DirectX::SimpleMath::Vector3 position);
	~Air();

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
		ShaderLambda option = nullptr) final;

public:

	// �Փ˂�ʒm����
	void NotificateHit(const bool& is) { is_hit = is; }

	// �A�N�e�B�u�t���O��؂�ւ���
	void SetActive(const bool flag) { is_active = flag; }

};

#endif // AIR