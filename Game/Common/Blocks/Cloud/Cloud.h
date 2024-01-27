/*
 *	@File	Cloud.h
 *	@Brief	�_�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLOUD
#define CLOUD

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Cloud : public IGameObject
{
private:

	// �������W
	DirectX::SimpleMath::Vector3 m_arrivePosition;

	// �Փ˃t���O
	bool is_hit;

	// �����t���O
	bool is_arrive;

private:

	// ��]���x
	static const float ROTATE_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	/// <returns>�Ȃ�</returns>
	Cloud(DirectX::SimpleMath::Vector3 position);
	~Cloud();

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

	// �Փ˂�ʒm����
	void NotificateHit(const bool& is) { is_hit = is; }

};

#endif // CLOUD