/*
 *  @File   BG_Select.cpp
 *  @Brief  バックグラウンド。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "BG_Select.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float BG_Select::ALPHA = 0.65f;		// アルファ値

//==============================================================================
// コンストラクタ
//==============================================================================
BG_Select::BG_Select()
{
	m_sprite = std::make_unique<DrawSprite>();
}

//==============================================================================
// デストラクタ
//==============================================================================
BG_Select::~BG_Select()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void BG_Select::Initialize()
{
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"back", L"Resources/Textures/BackGround/selectBG.dds");
}

//==============================================================================
// 描画関数
//==============================================================================
void BG_Select::Draw()
{
	m_sprite->DrawTexture(L"back", SimpleMath::Vector2::Zero,
		SimpleMath::Vector4::One * ALPHA, SimpleMath::Vector2::One, SimpleMath::Vector2::Zero);
}
