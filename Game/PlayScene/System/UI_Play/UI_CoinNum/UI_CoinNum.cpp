/*
 *  @File   UI_CoinNum.cpp
 *  @Brief  プレイシーンのUIのコイン数。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "UI_CoinNum.h"

//==============================================================================
// 定数の設定
//==============================================================================
const UINT UI_CoinNum::SIZE = 64U;			// スプライトのサイズ

//==============================================================================
// エイリアス宣言
//==============================================================================
using ValDigits = DrawNumber::Digits;		// 数字のディジット

//==============================================================================
// コンストラクタ
//==============================================================================
UI_CoinNum::UI_CoinNum()
	: m_position{}							// 座標
	, m_color{}								// 描画色
{
	// 数字作成
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_CoinNum::~UI_CoinNum()
{
	m_nums->reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void UI_CoinNum::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate)
{
	// 数字の設定
	m_nums[0]->SetPosition(pos);
	m_nums[0]->SetColor(color);
	m_nums[1]->SetPosition(m_nums[0]->GetPosition() + SimpleMath::Vector2(SIZE, 0.0f));
	m_nums[1]->SetColor(color);

	for (int i = 0; i < 2; i++)
	{
		m_nums[i]->SetScreenRate(rate);
	}
}

//==============================================================================
// 描画関数
//==============================================================================
void UI_CoinNum::Draw()
{
	// コインの枚数を描画
	m_nums[0]->Draw(m_coinNum, ValDigits::Ten);
	m_nums[1]->Draw(m_coinNum, ValDigits::One);
}