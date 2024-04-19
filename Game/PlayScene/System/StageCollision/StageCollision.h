/*
 *	@File	StageCollision.h
 *	@Brief	�X�e�[�W�̓����蔻��B
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef STAGECOLLISION
#define STAGECOLLISION

// �Q�[���I�u�W�F�N�g
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/Objects/Player/Player.h"

class StageCollision
{
public:

	// �R���X�g���N�^
	StageCollision();
	// �f�X�g���N�^
	~StageCollision();
	// ������
	void Initialize(BlockManager* blocks);
	// �X�V
	void Update(Player* player);

private:

	// �Փ˖�
	enum Side
	{
		None, Left, Right, Up, Down, Front, Behind
	};

	// ���E�����a
	static const float RADIUS;
	// ������
	static const int NUM_DIVISIONS = 8;

private:

	// �ŗL����
	void PerformEngenProc(Player* player, BaseObject* block, DirectX::SimpleMath::Vector3 newPos, Side side);

	// �����蔻�菈��
	Side IsCube(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale);

private:

	// ����I�u�W�F�N�g�z��
	std::vector<BaseObject*> m_objects;

};

#endif // STAGECOLLISION