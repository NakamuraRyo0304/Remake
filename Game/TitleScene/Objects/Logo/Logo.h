/*
 *	@File	Logo.h
 *	@Brief	�^�C�g�����S�I�u�W�F�N�g�B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Logo : public IGameObject
{
private:

	// �ړ��ʒu��
	static const DirectX::SimpleMath::Vector3 MOVE_POS;

	// ���f���̃T�C�Y
	static const float MODEL_SCALE;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Logo();
	~Logo();

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
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) override;

};

#endif // LOGO