/*
 *  @File   Seal.cpp
 *  @Brief  �V�[���B
 *  @Date   2024-02-15
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Seal.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Seal::Seal(const wchar_t* path)
	: m_position{}	// ���W
	, m_scRate{}	// ��ʊg�嗦
	, m_rate{}		// �摜�g�嗦
{
	m_sprite = std::make_unique <DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"Seal", path);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Seal::~Seal()
{
	m_sprite.reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void Seal::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 scRate, float rotate)
{
	// �e��ݒ�
	m_sprite->CreateRotation(L"Seal", rotate);
	m_position = pos;
	m_rate = rate;
	m_scRate = scRate;
}

//==============================================================================
// �`��֐�
//==============================================================================
void Seal::Draw()
{
	m_sprite->DrawTexture(L"Seal", m_position * m_scRate, SimpleMath::Vector4::One,
		m_rate * m_scRate, SimpleMath::Vector2(128.0f, 128.0f), {0U,0U,256U,256U});
}
