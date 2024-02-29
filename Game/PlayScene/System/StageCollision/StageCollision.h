/*
 *	@File	StageCollision.h
 *	@Brief	�X�e�[�W�̓����蔻��B
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef STAGECOLLISION
#define STAGECOLLISION

//==============================================================================
// �Q�[���I�u�W�F�N�g
//==============================================================================
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/Objects/Player/Player.h"

class StageCollision
{
private:

	// �Փ˖�
	enum Side
	{
		None, Left, Right, Up, Down, Front, Behind
	};

	// ����I�u�W�F�N�g�z��
	std::vector<IGameObject*> m_objects;

	// ���E�����a
	static const float RADIUS;

	// ������
	static const int NUM_DIVISIONS = 8;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	StageCollision();
	~StageCollision();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="blocks">�u���b�N�}�l�[�W���|�C���^</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(BlockManager* blocks);

	/// <summary>
	/// �����蔻��̍X�V
	/// </summary>
	/// <param name="player">�v���C���[�|�C���^</param>
	/// <returns>�Ȃ�</returns>
	void Update(Player* player);

private:

	/// <summary>
	/// �ŗL����
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="block">�u���b�N</param>
	/// <param name="newPos">�ύX��̍��W</param>
	/// <param name="side">����������</param>
	/// <returns>�Ȃ�</returns>
	void PerformEngenProc(Player* player, IGameObject* block, DirectX::SimpleMath::Vector3 newPos, Side side);

	/// <summary>
	/// �����蔻�菈��
	/// </summary>
	/// <param name="playerPos">�v���C���[���W</param>
	/// <param name="blockPos">�u���b�N���W</param>
	/// <param name="playerScale">�v���C���[�X�P�[��</param>
	/// <param name="blockScale">�u���b�N�X�P�[��</param>
	/// <returns>�Փ˖�</returns>
	Side IsCube(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale);
};

#endif // STAGECOLLISION