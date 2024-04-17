/*
 *  @File   BG_Select.h
 *  @Brief  バックグラウンド。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BG_SELECT
#define BG_SELECT

class DrawSprite;
class BG_Select
{
public:

	// コンストラクタ
	BG_Select();
	// デストラクタ
	~BG_Select();
	// 初期化
	void Initialize();
	// 描画
	void Draw();

private:

	// アルファ値
	static const float ALPHA;

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

};

#endif // BG_SELECT