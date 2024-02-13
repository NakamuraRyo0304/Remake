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
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	BG_Clear();
	~BG_Clear();

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

#endif // BG_CLEAR