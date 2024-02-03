/*
 *	@File	IGameObjectStates.h
 *	@Brief	�Q�[���I�u�W�F�N�g�̃X�e�[�^�X�錾�B
 *	@Date	2023-11-18
 *  @Author NakamuraRyo
 */

#pragma once

/// <summary>
/// �I�u�W�F�N�gID
/// Back:�w�i��|Obj:���肠��I�u�W�F�N�g
/// </summary>
enum class ID
{
	Default,		// �ݒ�Ȃ�
	Back_Bird,		// �^�C�g���̒�
	Back_Logo,		// ���S
	Back_Sky,		// �X�J�C�h�[��
	Obj_Player,		// �v���C��
	Obj_Air,		// �G�f�B�^�p����u���b�N
	Obj_Sand,		// ���u���b�N
	Obj_Coin,		// �R�C���u���b�N
	Obj_Cloud,		// �_�u���b�N
	Obj_Goal,		// �S�[���I�u�W�F�N�g
	Deleted,		// �폜�ς�
	Length,			// �SID��
};

// �d������
constexpr double NON_WEIGHT = -1.0;