/*
 *  @File   UI_PlayArea.cpp
 *  @Brief  �v���C�V�[����UI�̃G���A�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "UI_PlayArea.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_PlayArea::UI_PlayArea()
	: m_position{}							// ���W
	, m_color{}								// �`��F
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// �X�v���C�g�̓o�^
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_PlayArea::~UI_PlayArea()
{
	m_sprites.reset();
}

//==============================================================================
// �`�悷��
//==============================================================================
void UI_PlayArea::Draw(SimpleMath::Vector2 ScreenRate)
{
	m_sprites->DrawTexture(L"Area",
		m_position * ScreenRate, m_color,
		SimpleMath::Vector2::One * ScreenRate, SimpleMath::Vector2::Zero);
}
