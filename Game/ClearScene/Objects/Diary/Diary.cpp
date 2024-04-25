/*
 *  @File   Diary.cpp
 *  @Brief  日記。
 *  @Date   2024-04-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Libraries/UserUtility.h"
#include "Diary.h"

// コンストラクタ
Diary::Diary()
	:
	m_color(UserUtility::ColorsVector::BLACK)	// 色
{
	m_sprite = std::make_unique<DrawSprite>();
	m_color.w = 0.0f;	// アルファを０にする
}

// デストラクタ
Diary::~Diary()
{
	m_sprite.reset();
}

// 初期化
void Diary::Initialize(float time, int collect, int maxCoin)
{
	// それぞれの割合を計算する
	std::wstring times = CalcTimePer(time);
	std::wstring coins = CalcCoinPer(collect, maxCoin);

	// 画像作成
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"Time", times);
	m_sprite->AddTextureData(L"Coin", coins);
	m_sprite->AddTextureData(L"Note", L"Resources/Textures/Diary/Note.dds");

}

// 更新
void Diary::Update()
{
	// アルファをフェードイン
	m_color.w = UserUtility::Lerp(m_color.w, 1.0f);
}

// 描画
void Diary::Draw()
{
	m_sprite->DrawTexture(L"Note", { 50.0f,864.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,192 });
	m_sprite->DrawTexture(L"Time", { 50.0f,928.0f }, m_color,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,64 });
	m_sprite->DrawTexture(L"Coin", { 50.0f,972.0f }, m_color,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,64 });
}

// 時間から文字列を取得
std::wstring Diary::CalcTimePer(const float& time) const
{
    if (time >= 30.0f) // 30秒
        return L"Resources/Textures/Diary/TextTimeMax.dds"; // "長い"
    else if (time >= 15.0f) // 15秒
        return L"Resources/Textures/Diary/TextTimeMid.dds"; // "中間"
    else
        return L"Resources/Textures/Diary/TextTimeMin.dds"; // "短い"
}

// コインの取得率から文字列を取得
std::wstring Diary::CalcCoinPer(const int& collect, const int& max) const
{
    float percent = static_cast<float>(collect) / static_cast<float>(max);

    if (percent >= 0.8f) // 80%
        return L"Resources/Textures/Diary/TextCoinMax.dds"; // "多い"
    else if (percent >= 0.5f) // 50%
        return L"Resources/Textures/Diary/TextCoinMid.dds"; // "ちょうど"
    else
        return L"Resources/Textures/Diary/TextCoinMin.dds"; // "少ない"
}
