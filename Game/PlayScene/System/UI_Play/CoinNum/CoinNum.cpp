/*
 *  @File   CoinNum.cpp
 *  @Brief  �v���C�V�[����UI�̃R�C�����B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "CoinNum.h"

// �萔�̐ݒ�
const UINT CoinNum::SIZE = 64U;			// �X�v���C�g�̃T�C�Y

// �G�C���A�X�錾
using ValDigits = DrawNumber::Digits;		// �����̃f�B�W�b�g

// �R���X�g���N�^
CoinNum::CoinNum()
	:
	m_position(),						// ���W
	m_color(),							// �`��F
	m_coinNum(0),						// �R�C����
	m_maxCoinNum(0)						// �ő�R�C����

{
	// �����쐬
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}
}

// �f�X�g���N�^
CoinNum::~CoinNum()
{
	m_nums->reset();
}

// ������
void CoinNum::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate, SimpleMath::Vector2 scRate)
{
	// ���W�̐ݒ�
	m_position = pos;

	// �����̐ݒ�
	m_nums[0]->SetPosition(pos);
	m_nums[0]->SetColor(color);
	m_nums[1]->SetPosition(m_nums[0]->GetPosition() + SimpleMath::Vector2(SIZE, 0.0f));
	m_nums[1]->SetColor(color);

	for (int i = 0; i < 2; i++)
	{
		m_nums[i]->SetRate(rate);
		m_nums[i]->SetScreenRate(scRate);
	}
}

// �`��
void CoinNum::Draw()
{
	// �R�C���̖�����`��
	m_nums[0]->Draw(m_coinNum, ValDigits::Ten);
	m_nums[1]->Draw(m_coinNum, ValDigits::One);
}