/*
 *	@File	SystemManager.cpp
 *	@Brief	�Q�[�����쐬���邽�߂̃V�X�e���̊Ǘ��N���X�B
 *	@Date	2023-06-02
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SystemManager.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
SystemManager::SystemManager()
	: m_states{nullptr}
	, m_camera{nullptr}
	, m_sprite{nullptr}
	, m_raycast{nullptr}
	, m_gridFloor{nullptr}
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
SystemManager::~SystemManager()
{
	delete m_states;
	delete m_camera;
	delete m_sprite;
	delete m_raycast;
	delete m_gridFloor;
}

//==============================================================================
// �R�����X�e�[�g
//==============================================================================
CommonStates* SystemManager::GetCommonStates()
{
	if (not m_states)
	{
		m_states = new CommonStates(DX::DeviceResources::GetInstance()->GetD3DDevice());
	}
	return m_states;
}

//==============================================================================
// �m�[�}���J����
//==============================================================================
Camera* SystemManager::GetCamera()
{
	if (not m_camera)
	{
		m_camera = new Camera();
	}
	return m_camera;
}

//==============================================================================
// �X�v���C�g
//==============================================================================
DrawSprite* SystemManager::GetDrawSprite()
{
	if (not m_sprite)
	{
		m_sprite = new DrawSprite();
	}
	return m_sprite;
}

//==============================================================================
// ���C�L���X�g
//==============================================================================
RayCast* SystemManager::GetRayCast()
{
	if (not m_raycast)
	{
		m_raycast = new RayCast();
	}
	return m_raycast;
}

//==============================================================================
// �O���b�h�t���A
//==============================================================================
Debug::GridFloor* SystemManager::GetGridFloor()
{
	if (not m_gridFloor)
	{
		m_gridFloor = new Debug::GridFloor(50, 50);
	}
	return m_gridFloor;
}

//==============================================================================
// �����쐬�֐�
//==============================================================================
void SystemManager::CreateResources()
{
	// �`��ݒ�
	GetCommonStates();

	// �J�����̏�����
	GetCamera();

	// �摜�̕`��
	GetDrawSprite();

	// ���C���΂�
	GetRayCast();

	// �O���b�h�t���A
	GetGridFloor();
}