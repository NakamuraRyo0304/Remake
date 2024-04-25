/*
 *  @File   Diary.h
 *  @Brief  日記。
 *  @Date   2024-04-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DIARY
#define DIARY

class DrawSprite;
class Diary
{
public:

	// コンストラクタ
	Diary();
	// デストラクタ
	~Diary();
	// 初期化
	void Initialize(float time, int collect, int maxCoin);
	// 更新
	void Update();
	// 描画
	void Draw();

private:

	// 割合を求めて文字列を取得
	std::wstring CalcTimePer(const float& time) const;
	std::wstring CalcCoinPer(const int& collect, const int& max) const;

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;
	// 色
	DirectX::SimpleMath::Vector4 m_color;
};

#endif // DIARY