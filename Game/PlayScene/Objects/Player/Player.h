/*
 *	@File	Player.h
 *	@Brief	�v���C���[�B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYER
#define PLAYER

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"
// �v���C���[�X�e�[�g
#include "MoveStates.h"
// �v���C���[�̃p�[�c
#include "Parts/Head.h"

class Player : public BaseObject
{
public:

	// �t�H���[�p�X���擾
	std::vector<DirectX::SimpleMath::Vector3>& GetFollowPath() { return m_goalPoints; }
	// �t�H���[�p�X��ǉ�
	void AddFollowPath(const DirectX::SimpleMath::Vector3& path, const int& max);
	// �i�[���Ă���p�X��S�폜
	void ResetGoalPosition() { m_goalPoints.clear(); }
	// �R�C���������擾
	int GetCoinNum() const { return m_coinNum; }
	// �R�C���������J�E���g�A�b�v
	void CountUpCoins() { m_coinNum++; }
	// �R�C���Փ˃t���O���擾
	bool IsCoinHit() const { return is_coinHit; }
	// �R�C���Փ˃t���O��ݒ�
	void SetCoinHit(const bool& isHit) { is_coinHit = isHit; }
	// �����t���O���擾
	bool IsFall() const { return is_fall; }
	// �����t���O��ݒ�
	void SetFall(const bool& isFall) { is_fall = isFall; }
	// ���S�t���O���擾
	bool IsDeath() const { return is_death; }
	// ���S�t���O��ݒ�
	void SetDeath(const bool& isDeath) { is_death = isDeath; }

public:

	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

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

private:

	// ��
	std::unique_ptr<Head> m_head;
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

};

#endif // PLAYER