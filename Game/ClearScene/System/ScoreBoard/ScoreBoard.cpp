/*
 *  @File   ScoreBoard.cpp
 *  @Brief  ゲームのスコアを表示する。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "ScoreBoard.h"

// 定数の設定
const UINT ScoreBoard::SIZE = 128U;			// スプライトのサイズ
// エイリアス宣言
using ValDigits = DrawNumber::Digits;		// 数字のディジット

// コンストラクタ
ScoreBoard::ScoreBoard()
	:
	m_position(),							// 座標
	m_color(),								// 描画色
	m_number()								// 数値
{
	// 数字作成
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}
}

// デストラクタ
ScoreBoard::~ScoreBoard()
{
	m_nums->reset();
}

// 初期化
void ScoreBoard::Initialize(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate, SimpleMath::Vector2 scRate, double span)
{
	// 数字の設定
	m_nums[0]->SetPosition(pos);
	m_nums[1]->SetPosition(m_nums[0]->GetPosition() +
		SimpleMath::Vector2(SIZE * static_cast<float>(span), 0.0f) * rate);

	for (int i = 0; i < 2; i++)
	{
		m_nums[i]->SetColor(color);
		m_nums[i]->SetRate(rate);
		m_nums[i]->SetScreenRate(scRate);
	}
}

// 描画
void ScoreBoard::Draw()
{
	m_nums[0]->Draw(m_number, ValDigits::Ten);
	m_nums[1]->Draw(m_number, ValDigits::One);
}