/*
 *  @File   DrawNumber.cpp
 *  @Brief  �����̕`��N���X�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawNumber.h"

// �萔�̐ݒ�
const UINT DrawNumber::SIZE = 128;		// �P�������̃T�C�Y

// �R���X�g���N�^
DrawNumber::DrawNumber()
	:
	m_position(),				// ���W
	m_origin(),					// ���S���W
	m_rate(),					// �����g�嗦
	m_screenRate(),				// ��ʊg�嗦
	m_rect(),					// �؂���ʒu
	m_color()					// �F
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"num", L"Resources/Textures/Text/Number.dds");

	// ������
	m_position = m_origin = SimpleMath::Vector2::Zero;
	m_screenRate = SimpleMath::Vector2::One;
	m_color = SimpleMath::Vector4::One;
	m_rate = SimpleMath::Vector2::One;
}

// �f�X�g���N�^
DrawNumber::~DrawNumber()
{
	m_sprite.reset();
}

// �`��
void DrawNumber::Draw(UINT num, Digits digits)
{
	UINT number = num;

	// �`�悷�錅�����v�Z
	if (digits == Digits::One)
	{
		number = num % 10;
		if (number < 1) number = 0;
	}
	if (digits == Digits::Ten)
	{
		number = num / 10;

		if (number < 1) number = 0;
	}

	// ������؂���
	m_rect = Cut(number);

	// ������`��
	m_sprite->DrawTexture(L"num", m_position * m_screenRate,
		m_color, m_screenRate * m_rate, m_origin, m_rect);
}

// ������؂���
RECT_U DrawNumber::Cut(UINT num)
{
	RECT_U rect;
	UINT number = num;

	// ������5-9�̏ꍇ�͉��i
	if (number >= 5)
	{
		rect.top = SIZE;
		rect.bottom = SIZE * 2;			// �㉺�̐؂蕪��
		number -= 5;					// �O�|�S�̐؂蕪�������ɕϊ�
										// ��jnum��6�̏ꍇ��1�̏���
		// ���E�̐؂蕪������
		rect.left = number * SIZE;		// ���E��؂蕪��
		rect.right = rect.left + SIZE;
	}
	else
	{
		rect.top = 0U;
		rect.bottom = SIZE;				// �㉺�̐؂蕪��

		// ���E�̐؂蕪������
		rect.left = num * SIZE;			// ���E��؂蕪��
		rect.right = rect.left + SIZE;
	}

	return rect;
}
