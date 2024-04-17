/*
 *  @File   Logo.cpp
 *  @Brief  タイトルロゴ。
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Logo.h"

// 定数の設定
const RECT_U Logo::SIZE = RECT_U(0, 0, 576, 224);		// 画像サイズ

// コンストラクタ
Logo::Logo(SimpleMath::Vector2 scRate)
	:
	m_screenRate(scRate),			// 画面比率
	m_position(),					// 座標
	m_color(),						// 色
	m_rate()						// 拡大率
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

// デストラクタ
Logo::~Logo()
{
	m_sprite.reset();
}

// 初期化
void Logo::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color, SimpleMath::Vector2 rate)
{
	m_sprite->AddTextureData(L"Logo", L"Resources/Textures/Logo/Logo.dds");
	m_position = pos;
	m_color = color;
	m_rate = rate;
}

// 描画
void Logo::Draw()
{
	m_sprite->DrawTexture(L"Logo", m_position * m_screenRate, m_color,
		m_rate * m_screenRate, SimpleMath::Vector2::Zero, SIZE);
}
