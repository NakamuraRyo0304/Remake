/*
 *  @File   Logo.cpp
 *  @Brief  �^�C�g�����S�B
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Logo.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Logo::Logo(SimpleMath::Vector2 scRate)
	: m_screenRate{ scRate }			// ��ʔ䗦
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Logo::~Logo()
{
	m_sprite.reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void Logo::Initialize()
{
	m_sprite->AddTextureData(L"Logo", L"Resources/Textures/Logo/Logo.dds");
}
