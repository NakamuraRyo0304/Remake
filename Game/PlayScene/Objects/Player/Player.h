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
// �v���C���[�X�e�[�g
//==============================================================================
#include "MoveStates.h"

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

	// �R�C���Փ˃t���O
	bool is_coinHit;

private:

	// ��
	std::unique_ptr<Head> m_head;

private:

	// �ō����x
	static const float MAX_SPEED;
	// �ō����ňړ�����͈�
	static const float RANGE;
	// �����͈�
	static const float ARRIVE_RADIUS;
	// �ړI�n�����̒��ߎ���
	static const float GIVEUP_TIME;
	// ���񑬓x
	static const float ROTATE_SPEED;
	// �d��
	static const float GRAVITY;
	// ���S���C��
	static const float DEATH_LINE;
	// ���S���̉�]
	static const float DEATH_ROTATE;
	// ���f���̃X�P�[��
	static const float SCALE;

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
	/// <param name="wireframe">���C���[�t���[��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

public:

	// �t�H���[�p�X��ݒ�
	void AddFollowPath(const DirectX::SimpleMath::Vector3& path, const int& max);

	// ���݊i�[���Ă���p�X���擾
	std::vector<DirectX::SimpleMath::Vector3>& GetFollowPath() { return m_goalPoints; }
	// �i�[���Ă���p�X��S�폜
	void ResetGoalPosition() { m_goalPoints.clear(); }

	// �R�C���������擾
	int GetCoinNum() const { return m_coinNum; }
	// �R�C���������J�E���g�A�b�v
	void CountUpCoins() { m_coinNum++; }

	// �R�C���Փ˃t���O���擾
	bool IsCoinHit() const { return is_coinHit; }
	void SetCoinHit(const bool& isHit) { is_coinHit = isHit; }

	// �����t���O���擾
	bool IsFall() const { return is_fall; }
	// �����t���O��ݒ�
	void SetFall(const bool& isFall) { is_fall = isFall; }

	// ���S�t���O���擾
	bool IsDeath() const { return is_death; }
	// ���S�t���O��ݒ�
	void SetDeath(const bool& isDeath) { is_death = isDeath; }
};

#endif // PLAYER