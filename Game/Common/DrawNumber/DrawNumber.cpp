/*
 *  @File   DrawNumber.cpp
 *  @Brief  数字の描画クラス。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawNumber.h"

// 定数の設定
const UINT DrawNumber::SIZE = 128;		// １数字分のサイズ

// コンストラクタ
DrawNumber::DrawNumber()
	:
	m_position(),				// 座標
	m_origin(),					// 中心座標
	m_rate(),					// 文字拡大率
	m_screenRate(),				// 画面拡大率
	m_rect(),					// 切り取り位置
	m_color()					// 色
{
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"num", L"Resources/Textures/Text/Number.dds");

	// 初期化
	m_position = m_origin = SimpleMath::Vector2::Zero;
	m_screenRate = SimpleMath::Vector2::One;
	m_color = SimpleMath::Vector4::One;
	m_rate = SimpleMath::Vector2::One;
}

// デストラクタ
DrawNumber::~DrawNumber()
{
	m_sprite.reset();
}

// 描画
void DrawNumber::Draw(UINT num, Digits digits)
{
	UINT number = num;

	// 描画する桁数を計算
	if (digits == Digits::One)
	{
		number = num % 10;
		if (number < 1) number = 0;
	}
	if (digits == Digits::Ten)
	{
		number = num / 10;

		if (number < 1) number = 0;
	}

	// 数字を切り取る
	m_rect = Cut(number);

	// 数字を描画
	m_sprite->DrawTexture(L"num", m_position * m_screenRate,
		m_color, m_screenRate * m_rate, m_origin, m_rect);
}

// 数字を切り取る
RECT_U DrawNumber::Cut(UINT num)
{
	RECT_U rect;
	UINT number = num;

	// 数字が5-9の場合は下段
	if (number >= 5)
	{
		rect.top = SIZE;
		rect.bottom = SIZE * 2;			// 上下の切り分け
		number -= 5;					// ０－４の切り分け処理に変換
										// 例）numが6の場合は1の処理
		// 左右の切り分け処理
		rect.left = number * SIZE;		// 左右を切り分け
		rect.right = rect.left + SIZE;
	}
	else
	{
		rect.top = 0U;
		rect.bottom = SIZE;				// 上下の切り分け

		// 左右の切り分け処理
		rect.left = num * SIZE;			// 左右を切り分け
		rect.right = rect.left + SIZE;
	}

	return rect;
}
