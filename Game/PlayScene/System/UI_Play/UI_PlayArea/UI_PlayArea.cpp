/*
 *  @File   UI_PlayArea.cpp
 *  @Brief  プレイシーンのUIのエリア。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "UI_PlayArea.h"

//==============================================================================
// コンストラクタ
//==============================================================================
UI_PlayArea::UI_PlayArea()
	: m_position{}							// 座標
	, m_color{}								// 描画色
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// スプライトの登録
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_PlayArea::~UI_PlayArea()
{
	m_sprites.reset();
}

//==============================================================================
// 描画する
//==============================================================================
void UI_PlayArea::Draw(SimpleMath::Vector2 ScreenRate)
{
	m_sprites->DrawTexture(L"Area",
		m_position * ScreenRate, m_color,
		SimpleMath::Vector2::One * ScreenRate, SimpleMath::Vector2::Zero);
}
