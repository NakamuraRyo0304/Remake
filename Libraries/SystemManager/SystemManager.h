/*
 *	@File	SystemManager.h
 *	@Brief	�Q�[�����쐬���邽�߂̃V�X�e���̊Ǘ��N���X�B
 *	@Date	2023-06-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SYSTEMMANAGER
#define SYSTEMMANAGER

#include "Game/GameMain.h"

//-------------------------------------------------------------------------------------//
// �V�X�e���̃C���N���[�h
#include "../SystemDatas/GridFloor/GridFloor.h"
#include "../SystemDatas/RayCast/RayCast.h"
#include "../SystemDatas/DrawSprite/DrawSprite.h"
//-------------------------------------------------------------------------------------//

class SystemManager
{
private:
	// �R�����X�e�[�g
	DirectX::CommonStates*			m_states;
	// �h���[�X�v���C�g
	DrawSprite*						m_sprite;
	// �O���b�h��
	Debug::GridFloor*               m_gridFloor;
	// ���C�L���X�g
	RayCast*						m_raycast;

public:
	// ���ʂ̍쐬
	void CreateResources();

	// �R�����X�e�[�g�̎擾
	DirectX::CommonStates* GetCommonStates();

	// �h���[�X�v���C�g�̎擾
	DrawSprite* GetDrawSprite();

	// ���C�L���X�g�̎擾
	RayCast* GetRayCast();

	// �O���b�h�t���A�̎擾
	Debug::GridFloor* GetGridFloor();

public:
	SystemManager();
	~SystemManager();
};

#endif // SYSTEMMANAGER