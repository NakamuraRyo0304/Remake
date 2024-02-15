/*
 *  @File   Seal.cpp
 *  @Brief  シール。
 *  @Date   2024-02-15
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Seal.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Seal::Seal(const wchar_t* path)
	: m_position{}	// 座標
	, m_scRate{}	// 画面拡大率
	, m_rate{}		// 画像拡大率
{
	m_sprite = std::make_unique <DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"Seal", path);
}

//==============================================================================
// デストラクタ
//==============================================================================
Seal::~Seal()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void Seal::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 scRate, float rotate)
{
	// 各種設定
	m_sprite->CreateRotation(L"Seal", rotate);
	m_position = pos;
	m_rate = rate;
	m_scRate = scRate;
}

//==============================================================================
// 描画関数
//==============================================================================
void Seal::Draw()
{
	m_sprite->DrawTexture(L"Seal", m_position * m_scRate, SimpleMath::Vector4::One,
		m_rate * m_scRate, SimpleMath::Vector2(128.0f, 128.0f), {0U,0U,256U,256U});
}
