/*
 *  @File   UI_PlayArea.cpp
 *  @Brief  プレイシーンのUIのエリア。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "UI_PlayArea.h"

// コンストラクタ
UI_PlayArea::UI_PlayArea()
	:
	m_position(),							// 座標
	m_color()								// 描画色
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// スプライトの登録
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");
}

// デストラクタ
UI_PlayArea::~UI_PlayArea()
{
	m_sprites.reset();
}

// 初期化
void UI_PlayArea::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate)
{
	m_position = pos;
	m_rate = rate;
	m_color = color;
}

// 描画
void UI_PlayArea::Draw()
{
	m_sprites->DrawTexture(L"Area",
		m_position * m_rate, m_color, m_rate, SimpleMath::Vector2::Zero);
}
