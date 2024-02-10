/*
 *  @File   MomentCanv.cpp
 *  @Brief  クリアした瞬間の画像を表示する。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MomentCanv.h"

//==============================================================================
// コンストラクタ
//==============================================================================
MomentCanv::MomentCanv()
{
	// スプライト描画の作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

//==============================================================================
// デストラクタ
//==============================================================================
MomentCanv::~MomentCanv()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void MomentCanv::Initialize()
{
	// スプライトの設定
	m_sprite->AddTextureData(L"PlayPic", L"Resources/Textures/ScreenShot/image.dds");
}

//==============================================================================
// 描画関数
//==============================================================================
void MomentCanv::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate, SimpleMath::Vector2 origin, RECT_U rect)
{
	m_sprite->DrawTexture(L"PlayPic", pos, color, rate, origin, rect);
}
