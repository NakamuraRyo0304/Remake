/*
 *  @File   Tape.cpp
 *  @Brief  テープ。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Tape.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Tape::Tape()
	: m_position{}	// 座標
	, m_scRate{}	// 画面拡大率
	, m_rate{}		// 画像拡大率
{
	m_sprite = std::make_unique <DrawSprite>();
}

//==============================================================================
// デストラクタ
//==============================================================================
Tape::~Tape()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void Tape::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 scRate, float rotate)
{
	m_sprite->MakeSpriteBatch();

	// 乱数を取得
	int _rand = static_cast<int>(UserUtility::Random(1, 4));

	if (_rand == 1 || _rand == 2)
	{
		m_sprite->AddTextureData(L"tape", L"Resources/Textures/UI_Clear/tape1.dds");
	}
	else
	{
		m_sprite->AddTextureData(L"tape", L"Resources/Textures/UI_Clear/tape2.dds");
	}

	// 各種設定
	m_sprite->CreateRotation(L"tape", rotate);
	m_position = pos;
	m_rate = rate;
	m_scRate = scRate;
}

//==============================================================================
// 描画関数
//==============================================================================
void Tape::Draw()
{
	m_sprite->DrawTexture(L"tape", m_position * m_scRate, UserUtility::ColorsVector::WHITE,
		m_rate * m_scRate, SimpleMath::Vector2(160.0f, 64.0f), {0U,0U,320U,128U});
}
