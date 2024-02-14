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
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

private:

	// アルファ値
	static const float ALPHA;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	BG_Select();
	~BG_Select();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();
};

#endif // BG_SELECT