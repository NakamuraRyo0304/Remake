/*
 *	@File	Goal.h
 *	@Brief	�S�[���I�u�W�F�N�g�B
 *	@Date	2024-02-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GOAL
#define GOAL

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Goal : public IGameObject
{
private:

	// �Փ˃t���O
	bool is_hit;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	/// <returns>�Ȃ�</returns>
	Goal(DirectX::SimpleMath::Vector3 position);
	~Goal();

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

	// �Փ˃t���O��ON�ɂ���(�S�[������͂P�x�̂���ON�̂�)
	void OnHitFlag() { is_hit = true; }

	// �t���O�擾
	bool IsHitFlag() const { return is_hit; }
};

#endif // GOAL