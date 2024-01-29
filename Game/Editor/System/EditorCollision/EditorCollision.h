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

	// ���[���h�}�E�X
	std::unique_ptr<WorldMouse> m_worldMouse;

	// �r���[�s��E�ˉe�s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

private:

	// �����蔻��̔��a
	static const float HIT_RADIUS;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	EditorCollision(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	~EditorCollision();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="object">�I�u�W�F�N�g�|�C���^</param>
	/// <param name="setting">�I�����Ă���u���b�N��ID</param>
	/// <returns>�Ȃ�</returns>
	void Update(IGameObject* object, ID setting);

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

public:

	// ���[���h�}�E�X�̍��W
	DirectX::SimpleMath::Vector3 GetWorldMousePosition();
};

#endif // EDITORCOLLISION