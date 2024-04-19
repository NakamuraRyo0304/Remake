/*
 *  @File   BaseScene.cpp
 *  @Brief  �V�[���̊��N���X�B
 *  @Date   2024-04-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "BaseScene.h"

// �R���X�g���N�^
BaseScene::BaseScene()
	:
	m_system{ std::make_shared<SystemManager>() },	// �V�X�e���}�l�[�W��
	m_nextScene(SCENE::NONE),						// ���̃V�[��
	m_windowSize(FULL_HD),							// ��ʂ̃T�C�Y
	m_fadeSpeed(4.0f),								// �t�F�[�h�̑��x
	m_fadeValue(0.0f),								// �t�F�[�h�̌��ݒl
	is_changeFlag(false),							// �V�[���؂�ւ��t���O
	is_fadeEnd(false)								// �t�F�[�h�I���t���O
{
}

// �f�X�g���N�^
BaseScene::~BaseScene()
{
	m_system.reset();
}
