/*
 *	@File	Player.h
 *	@Brief	�v���C���[�B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYER
#define PLAYER

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

//==============================================================================
// �v���C���[�̃p�[�c
//==============================================================================
#include "Parts/Head.h"

class Player : public IGameObject
{
private:

	// �ړI�n�L���[
	std::vector<DirectX::SimpleMath::Vector3> m_goalPoints;

	// �ړ���
	DirectX::SimpleMath::Vector3 m_velocity;

	// �ړ��M�u�A�b�v�^�C��
	float m_giveUpTime;

	// ���L�R�C������
	int m_coinNum;

	// �����t���O
	bool is_fall;

	// ���S�t���O
	bool is_death;

private:

	// ��
	std::unique_ptr<Head> m_head;

private:

	// �ő�̃p�X��
	static const int MAX_PATH_NUM;

	// �ō����x
	static const float MAX_SPEED;

	// �ō����ňړ�����͈�
	static const float MS_RADIUS;

	// �����͈�
	static const float ARRIVE_RADIUS;

	// �ړI�n�����̒��ߎ���
	static const float GIVEUP_TIME;

	// ���S���C��
	static const float DEATH_LINE;

	// ���S���̉�]
	static const float DEATH_ROTATE;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Player();
	~Player();

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

public:

	// �t�H���[�p�X��ݒ�
	void PushBackFollowPath(DirectX::SimpleMath::Vector3 path);

	// ���݊i�[���Ă���p�X�̐����擾
	const std::vector<DirectX::SimpleMath::Vector3>& GetGoalPoints() { return m_goalPoints; }
	// �i�[���Ă���p�X��S�폜
	void ResetGoalPosition() { m_goalPoints.clear(); }

	// �R�C���������擾
	const int& GetCoinNum() { return m_coinNum; }
	// �R�C���������J�E���g�A�b�v
	void CountUpCoins() { m_coinNum++; }

	// �����t���O���擾
	const bool& IsFall() { return is_fall; }
	// �����t���O��ݒ�
	void SetFall(const bool& isFall) { is_fall = isFall; }

	// ���S�t���O���擾
	const bool& IsDeath() { return is_death; }
	// ���S�t���O��ݒ�
	void SetDeath(const bool& isDeath) { is_death = isDeath; }
};

#endif // PLAYER