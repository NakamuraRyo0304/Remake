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

	// 座標
	DirectX::SimpleMath::Vector2 m_position;

	// 画面拡大率
	DirectX::SimpleMath::Vector2 m_screenRate;

private:

	// 最終座標
	static const DirectX::SimpleMath::Vector2 LAST_POSITION;

	// 画像の回転角度
	static const float LAST_ROTATE;

	// 移動・回転速度
	static const float SPEED_TO_LAST;

	// 画面外の座標
	static const DirectX::SimpleMath::Vector2 OUT_POSITION;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenRate">画面拡大率</param>
	/// <returns>なし</returns>
	MomentCanv(DirectX::SimpleMath::Vector2 screenRate);
	~MomentCanv();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

	/// <summary>
	/// 更新関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="color">色</param>
	/// <param name="rate">拡大率</param>
	/// <param name="origin">中心位置</param>
	/// <param name="rect">切り取り位置</param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 origin, RECT_U rect);
};

#endif // MOMENTCANV