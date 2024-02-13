/*
 *  @File   DrawNumber.cpp
 *  @Brief  数字の描画クラス。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "DrawNumber.h"

//==============================================================================
// 定数の設定
//==============================================================================
const UINT DrawNumber::SIZE = 128;		// １数字分のサイズ

//==============================================================================
// コンストラクタ
//==============================================================================
DrawNumber::DrawNumber()
	: m_position{}		// 座標
	, m_origin{}		// 中心座標
	, m_rate{}			// 文字拡大率
	, m_screenRate{}	// 画面拡大率
	, m_rect{}			// 切り取り位置
	, m_color{}			// 色
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

//==============================================================================
// デストラクタ
//==============================================================================
DrawNumber::~DrawNumber()
{
	m_sprite.reset();
}

//==============================================================================
// 数字を描画する
//==============================================================================
void DrawNumber::Draw(UINT num, Digits digits)
{
	UINT _tmp = num;

	// 描画する桁数を計算
	if (digits == Digits::One)
	{
		_tmp = num % 10;
		if (_tmp < 1) _tmp = 0;
	}
	if (digits == Digits::Ten)
	{
		_tmp = num / 10;

		if (_tmp < 1) _tmp = 0;
	}

	// 数字を切り取る
	m_rect = Cut(_tmp);

	// 数字を描画
	m_sprite->DrawTexture(L"num", m_position * m_screenRate,
		m_color, m_screenRate * m_rate, m_origin, m_rect);
}

//==============================================================================
// 数字を切り取る
//==============================================================================
RECT_U DrawNumber::Cut(UINT num)
{
	RECT_U _rect;
	UINT _tmpNum = num;

	// 数字が5-9の場合は下段
	if (_tmpNum >= 5)
	{
		_rect.top = SIZE;
		_rect.bottom = SIZE * 2;			// 上下の切り分け
		_tmpNum -= 5;						// ０－４の切り分け処理に変換
											// 例）numが6の場合は1の処理
		// 左右の切り分け処理
		_rect.left = _tmpNum * SIZE;		// 左右を切り分け
		_rect.right = _rect.left + SIZE;
	}
	else
	{
		_rect.top = 0U;
		_rect.bottom = SIZE;				// 上下の切り分け

		// 左右の切り分け処理
		_rect.left = num * SIZE;			// 左右を切り分け
		_rect.right = _rect.left + SIZE;
	}

	return _rect;
}
