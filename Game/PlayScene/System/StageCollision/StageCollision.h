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

	// ���E�����a
	static const float RADIUS;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	StageCollision();
	~StageCollision();

	/// <summary>
	/// �����蔻��̍X�V
	/// </summary>
	/// <param name="player">�v���C���[�|�C���^</param>
	/// <param name="blocks">�u���b�N�}�l�[�W���|�C���^</param>
	/// <returns>�Ȃ�</returns>
	void Update(Player* player, BlockManager* blocks);

private:

	/// <summary>
	/// �����蔻�菈��
	/// </summary>
	/// <param name="playerPos">�v���C���[���W</param>
	/// <param name="blockPos">�u���b�N���W</param>
	/// <param name="playerScale">�v���C���[�X�P�[��</param>
	/// <param name="blockScale">�u���b�N�X�P�[��</param>
	/// <param name="push">�����߂����s���t���O�itrue�ŉ����߂��j</param>
	/// <returns>�Փ˖�</returns>
	Side IsCollision(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale, bool push = false);
};

#endif // STAGECOLLISION