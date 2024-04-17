/*
 *  @File   BG_Clear.cpp
 *  @Brief  �o�b�N�O���E���h�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "BG_Clear.h"

// �R���X�g���N�^
BG_Clear::BG_Clear()
{
	m_sprite = std::make_unique<DrawSprite>();
}

// �f�X�g���N�^
BG_Clear::~BG_Clear()
{
	m_sprite.reset();
}

// ������
void BG_Clear::Initialize()
{
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"back", L"Resources/Textures/BackGround/cork.dds");
}

// �`��
void BG_Clear::Draw()
{
	m_sprite->DrawTexture(L"back", SimpleMath::Vector2::Zero,
		SimpleMath::Vector4::One, SimpleMath::Vector2::One, SimpleMath::Vector2::Zero);
}
