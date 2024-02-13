/*
 *  @File   DrawNumber.cpp
 *  @Brief  �����̕`��N���X�B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawNumber.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const UINT DrawNumber::SIZE = 128;		// �P�������̃T�C�Y

//==============================================================================
// �R���X�g���N�^
//==============================================================================
DrawNumber::DrawNumber()
	: m_position{}		// ���W
	, m_origin{}		// ���S���W
	, m_rate{}			// �����g�嗦
	, m_screenRate{}	// ��ʊg�嗦
	, m_rect{}			// �؂���ʒu
	, m_color{}			// �F
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

//==============================================================================
// �f�X�g���N�^
//==============================================================================
DrawNumber::~DrawNumber()
{
	m_sprite.reset();
}

//==============================================================================
// ������`�悷��
//==============================================================================
void DrawNumber::Draw(UINT num, Digits digits)
{
	UINT _tmp = num;

	// �`�悷�錅�����v�Z
	if (digits == Digits::One)
	{
		_tmp = num % 10;
		if (_tmp < 1) _tmp = 0;
	}
	if (digits == Digits::Ten)
	{
		_tmp = num / 10;

		if (_tmp < 1) _tmp = 0;
	}

	// ������؂���
	m_rect = Cut(_tmp);

	// ������`��
	m_sprite->DrawTexture(L"num", m_position * m_screenRate,
		m_color, m_screenRate * m_rate, m_origin, m_rect);
}

//==============================================================================
// ������؂���
//==============================================================================
RECT_U DrawNumber::Cut(UINT num)
{
	RECT_U _rect;
	UINT _tmpNum = num;

	// ������5-9�̏ꍇ�͉��i
	if (_tmpNum >= 5)
	{
		_rect.top = SIZE;
		_rect.bottom = SIZE * 2;			// �㉺�̐؂蕪��
		_tmpNum -= 5;						// �O�|�S�̐؂蕪�������ɕϊ�
											// ��jnum��6�̏ꍇ��1�̏���
		// ���E�̐؂蕪������
		_rect.left = _tmpNum * SIZE;		// ���E��؂蕪��
		_rect.right = _rect.left + SIZE;
	}
	else
	{
		_rect.top = 0U;
		_rect.bottom = SIZE;				// �㉺�̐؂蕪��

		// ���E�̐؂蕪������
		_rect.left = num * SIZE;			// ���E��؂蕪��
		_rect.right = _rect.left + SIZE;
	}

	return _rect;
}
