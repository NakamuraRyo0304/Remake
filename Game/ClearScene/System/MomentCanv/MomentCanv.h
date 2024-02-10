/*
 *  @File   MomentCanv.h
 *  @Brief  クリアした瞬間の画像を表示する。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MOMENTCANV
#define MOMENTCANV

//==============================================================================
// スプライト描画クラス
//==============================================================================
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class MomentCanv
{
private:

	// スプライト描画
	std::unique_ptr<DrawSprite> m_sprite;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	MomentCanv();
	~MomentCanv();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="color">色</param>
	/// <param name="rate">拡大率</param>
	/// <param name="origin">中心位置</param>
	/// <param name="rect">切り取り位置</param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 origin, RECT_U rect);
};

#endif // MOMENTCANV