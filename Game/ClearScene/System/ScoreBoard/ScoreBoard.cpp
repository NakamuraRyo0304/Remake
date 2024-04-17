/*
 *  @File   ScoreBoard.cpp
 *  @Brief  �Q�[���̃X�R�A��\������B
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "ScoreBoard.h"

// �萔�̐ݒ�
const UINT ScoreBoard::SIZE = 128U;			// �X�v���C�g�̃T�C�Y
// �G�C���A�X�錾
using ValDigits = DrawNumber::Digits;		// �����̃f�B�W�b�g

// �R���X�g���N�^
ScoreBoard::ScoreBoard()
	:
	m_position(),							// ���W
	m_color(),								// �`��F
	m_number()								// ���l
{
	// �����쐬
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}
}

// �f�X�g���N�^
ScoreBoard::~ScoreBoard()
{
	m_nums->reset();
}

// ������
void ScoreBoard::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate, SimpleMath::Vector2 scRate, double span)
{
	// �����̐ݒ�
	m_nums[0]->SetPosition(pos);
	m_nums[1]->SetPosition(m_nums[0]->GetPosition() +
		SimpleMath::Vector2(SIZE * static_cast<float>(span), 0.0f) * rate);

	for (int i = 0; i < 2; i++)
	{
		m_nums[i]->SetColor(color);
		m_nums[i]->SetRate(rate);
		m_nums[i]->SetScreenRate(scRate);
	}
}

// �`��
void ScoreBoard::Draw()
{
	m_nums[0]->Draw(m_number, ValDigits::Ten);
	m_nums[1]->Draw(m_number, ValDigits::One);
}