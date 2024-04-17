/*
 *	@File	EditorCollision.h
 *	@Brief	�G�f�B�^�̓����蔻��B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCOLLISION
#define EDITORCOLLISION

// �u���b�N�}�l�[�W��
#include "Game/Common/BlockManager/BlockManager.h"

class WorldMouse;
class EditorCollision
{
public:

	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }

	// �R���X�g���N�^
	EditorCollision();
	// �f�X�g���N�^
	~EditorCollision();
	// �X�V
	void Update(IGameObject* object, ID setting);

private:

	// �����蔻��̔��a
	static const float HIT_RADIUS;

private:

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;

};

#endif // EDITORCOLLISION