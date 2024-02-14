/*
 *  @File   BG_Select.cpp
 *  @Brief  �o�b�N�O���E���h�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "BG_Select.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float BG_Select::ALPHA = 0.65f;		// �A���t�@�l

//==============================================================================
// �R���X�g���N�^
//==============================================================================
BG_Select::BG_Select()
{
	m_sprite = std::make_unique<DrawSprite>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
BG_Select::~BG_Select()
{
	m_sprite.reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void BG_Select::Initialize()
{
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"back", L"Resources/Textures/BackGround/selectBG.dds");
}

//==============================================================================
// �`��֐�
//==============================================================================
void BG_Select::Draw()
{
	m_sprite->DrawTexture(L"back", SimpleMath::Vector2::Zero,
		SimpleMath::Vector4::One * ALPHA, SimpleMath::Vector2::One, SimpleMath::Vector2::Zero);
}
