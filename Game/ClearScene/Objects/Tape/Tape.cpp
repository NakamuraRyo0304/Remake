/*
 *  @File   Tape.cpp
 *  @Brief  �e�[�v�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Tape.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Tape::Tape()
	: m_position{}	// ���W
	, m_scRate{}	// ��ʊg�嗦
	, m_rate{}		// �摜�g�嗦
{
	m_sprite = std::make_unique <DrawSprite>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Tape::~Tape()
{
	m_sprite.reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void Tape::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 scRate, float rotate)
{
	m_sprite->MakeSpriteBatch();

	// �������擾
	int _rand = static_cast<int>(UserUtility::Random(1, 4));

	if (_rand == 1 || _rand == 2)
	{
		m_sprite->AddTextureData(L"tape", L"Resources/Textures/UI_Clear/tape1.dds");
	}
	else
	{
		m_sprite->AddTextureData(L"tape", L"Resources/Textures/UI_Clear/tape2.dds");
	}

	// �e��ݒ�
	m_sprite->CreateRotation(L"tape", rotate);
	m_position = pos;
	m_rate = rate;
	m_scRate = scRate;
}

//==============================================================================
// �`��֐�
//==============================================================================
void Tape::Draw()
{
	m_sprite->DrawTexture(L"tape", m_position * m_scRate, UserUtility::ColorsVector::WHITE,
		m_rate * m_scRate, SimpleMath::Vector2(160.0f, 64.0f), {0U,0U,320U,128U});
}
