/*
 *  @File   DrawKeys.cpp
 *  @Brief  キー描画。
 *  @Date   2024-02-21
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "DrawKeys.h"

// コンストラクタ
DrawKeys::DrawKeys(const wchar_t* path, const SimpleMath::Vector2& pos, const SimpleMath::Vector2& screenRate)
	:
	m_position(pos),			// 座標
	m_scRate(screenRate),		// 画面拡大率
	m_rate()					// 拡大率
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_rate = SimpleMath::Vector2::One;
	m_sprite->AddTextureData(L"back", L"Resources/Textures/Keys/KeyCork.dds");
	m_sprite->AddTextureData(L"key", path);
}

// デストラクタ
DrawKeys::~DrawKeys()
{
	m_sprite.reset();
}

// 描画
void DrawKeys::Draw()
{
	// コルクの描画
	m_sprite->DrawTexture(L"back", m_position * m_scRate,
		SimpleMath::Vector4::One, m_rate * m_scRate, { 128.0f,128.0f }, { 0,0,256,256 });

	// キーの描画
	m_sprite->DrawTexture(L"key", m_position * m_scRate,
		m_color, m_rate * m_scRate, { 128.0f,128.0f }, { 0,0,256,256 });
}
