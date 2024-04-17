/*
 *  @File   Logo.cpp
 *  @Brief  �^�C�g�����S�B
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Logo.h"

// �萔�̐ݒ�
const RECT_U Logo::SIZE = RECT_U(0, 0, 576, 224);		// �摜�T�C�Y

// �R���X�g���N�^
Logo::Logo(SimpleMath::Vector2 scRate)
	:
	m_screenRate(scRate),			// ��ʔ䗦
	m_position(),					// ���W
	m_color(),						// �F
	m_rate()						// �g�嗦
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

// �f�X�g���N�^
Logo::~Logo()
{
	m_sprite.reset();
}

// ������
void Logo::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color, SimpleMath::Vector2 rate)
{
	m_sprite->AddTextureData(L"Logo", L"Resources/Textures/Logo/Logo.dds");
	m_position = pos;
	m_color = color;
	m_rate = rate;
}

// �`��
void Logo::Draw()
{
	m_sprite->DrawTexture(L"Logo", m_position * m_screenRate, m_color,
		m_rate * m_screenRate, SimpleMath::Vector2::Zero, SIZE);
}
