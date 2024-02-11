/*
 *  @File   UI_CoinNum.cpp
 *  @Brief  �v���C�V�[����UI�̃R�C�����B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "UI_CoinNum.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const UINT UI_CoinNum::SIZE = 64U;			// �X�v���C�g�̃T�C�Y

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using ValDigits = DrawNumber::Digits;		// �����̃f�B�W�b�g

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_CoinNum::UI_CoinNum()
	: m_position{}							// ���W
	, m_color{}								// �`��F
{
	// �����쐬
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_CoinNum::~UI_CoinNum()
{
	m_nums->reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void UI_CoinNum::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate)
{
	// �����̐ݒ�
	m_nums[0]->SetPosition(pos);
	m_nums[0]->SetColor(color);
	m_nums[1]->SetPosition(m_nums[0]->GetPosition() + SimpleMath::Vector2::UnitX * SIZE);
	m_nums[1]->SetColor(color);

	for (int i = 0; i < 2; i++)
	{
		m_nums[i]->SetRate(rate);
	}
}

//==============================================================================
// �`��֐�
//==============================================================================
void UI_CoinNum::Draw()
{
	// �R�C���̖�����`��
	m_nums[0]->Draw(m_coinNum, ValDigits::Ten);
	m_nums[1]->Draw(m_coinNum, ValDigits::One);
}