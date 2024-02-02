/*
 *	@File	EditorCollision.h
 *	@Brief	�G�f�B�^�̓����蔻��B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCOLLISION
#define EDITORCOLLISION

//==============================================================================
// �u���b�N�}�l�[�W��
//==============================================================================
#include "Game/Common/BlockManager/BlockManager.h"

class WorldMouse;
class EditorCollision
{
private:

	// ���W
	DirectX::SimpleMath::Vector3 m_position;

	// �r���[�s��E�ˉe�s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

private:

	// �����蔻��̔��a
	static const float HIT_RADIUS;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	EditorCollision();
	~EditorCollision();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="object">�I�u�W�F�N�g�|�C���^</param>
	/// <param name="setting">�I�����Ă���u���b�N��ID</param>
	/// <returns>�Ȃ�</returns>
	void Update(IGameObject* object, ID setting);

public:

	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
};

#endif // EDITORCOLLISION