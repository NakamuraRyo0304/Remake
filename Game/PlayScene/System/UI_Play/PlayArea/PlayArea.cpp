/*
 *  @File   PlayArea.cpp
 *  @Brief  �v���C�V�[����UI�̃G���A�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "PlayArea.h"

// �萔�̐ݒ�
const RECT_U PlayArea::RECT_BOARD = RECT_U(0, 0, 256, 572);	// �{�[�h�̐؂���ʒu

// �R���X�g���N�^
PlayArea::PlayArea()
	:
	m_position(),							// ���W
	m_color()								// �`��F
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// �X�v���C�g�̓o�^
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");
}

// �f�X�g���N�^
PlayArea::~PlayArea()
{
	m_sprites.reset();
}

// ������
void PlayArea::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate)
{
	m_position = pos;
	m_rate = rate;
	m_color = color;
}

// �`��
void PlayArea::Draw()
{
	m_sprites->DrawTexture(L"Area",
		m_position * m_rate, m_color, m_rate, SimpleMath::Vector2::Zero, RECT_BOARD);
}
