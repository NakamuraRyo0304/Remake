/*
 *  @File   Logo.cpp
 *  @Brief  タイトルロゴ。
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Logo.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Logo::Logo(SimpleMath::Vector2 scRate)
	: m_screenRate{ scRate }			// 画面比率
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

//==============================================================================
// デストラクタ
//==============================================================================
Logo::~Logo()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void Logo::Initialize()
{
	m_sprite->AddTextureData(L"Logo", L"Resources/Textures/Logo/Logo.dds");
}
