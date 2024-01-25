/*
 *	@File	IGameObjectStates.h
 *	@Brief	�Q�[���I�u�W�F�N�g�̃X�e�[�^�X�錾�B
 *	@Date	2023-11-18
 *  @Author NakamuraRyo
 */

#pragma once

// �I�u�W�F�N�gID
enum class ID
{
	Default,		// �ݒ�Ȃ�
	Player,			// �v���C���[
	Enemy,			// �G
	Item,			// �A�C�e��
	Length,			// �SID��
};

// �d������
constexpr double NON_WEIGHT = -1.0;