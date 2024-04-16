/*
 *  @File   BG_Clear.cpp
 *  @Brief  バックグラウンド。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "BG_Clear.h"

// コンストラクタ
BG_Clear::BG_Clear()
{
	m_sprite = std::make_unique<DrawSprite>();
}

// デストラクタ
BG_Clear::~BG_Clear()
{
	m_sprite.reset();
}

// 初期化
void BG_Clear::Initialize()
{
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"back", L"Resources/Textures/BackGround/cork.dds");
}

// 描画
void BG_Clear::Draw()
{
	m_sprite->DrawTexture(L"back", SimpleMath::Vector2::Zero,
		SimpleMath::Vector4::One, SimpleMath::Vector2::One, SimpleMath::Vector2::Zero);
}
