/*
 *  @File   BG_Clear.h
 *  @Brief  バックグラウンド。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BG_CLEAR
#define BG_CLEAR

class DrawSprite;
class BG_Clear
{
public:

	// コンストラクタ
	BG_Clear();
	// デストラクタ
	~BG_Clear();
	// 初期化
	void Initialize();
	/// 描画
	void Draw();

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;
};

#endif // BG_CLEAR