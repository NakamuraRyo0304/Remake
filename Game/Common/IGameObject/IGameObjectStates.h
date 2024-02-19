/*
 *	@File	IGameObjectStates.h
 *	@Brief	�Q�[���I�u�W�F�N�g�̃X�e�[�^�X�錾�B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once

/// <summary>
/// �I�u�W�F�N�gID
/// �I�u�W�F�N�g�̔�����\�ɂ���
/// </summary>
enum class ID
{
	Default,		// �ݒ�Ȃ�
	Back_Bird,		// �^�C�g���̒�
	Back_Logo,		// ���S
	Back_Sky,		// �X�J�C�h�[��
	Obj_Player,		// �v���C��
	Obj_Flag,		// �v���C�����ǐՂ����
	Obj_Air,		// �G�f�B�^�p����u���b�N
	Obj_Flozen,		// �X���u���b�N
	Obj_Coin,		// �R�C���u���b�N
	Obj_Cloud,		// �_�u���b�N
	Obj_Goal,		// �S�[���I�u�W�F�N�g
	Obj_Spike,		// ���I�u�W�F�N�g
	Obj_Lift,		// ���t�g�u���b�N


	CursorPos,		// �J�[�\����3D�ʒu
	Back_Iceberg,	// �X�R
	Back_Island,	// �Ǔ�




	////////////////
	//// ����ID ////
	////////////////

	Deleted,		// �폜�ς�
	Length,			// �SID��
};

// �d������
constexpr double NON_WEIGHT = -1.0;