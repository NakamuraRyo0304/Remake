/*
 *  @File   MomentCanv.h
 *  @Brief  クリアした瞬間の画像を表示する。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MOMENTCANV
#define MOMENTCANV

// スプライト描画クラス
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class MomentCanv
{
public:

	// 動作の終了状況を取得する
	bool IsEndMoving() const { return is_endMoving; }

public:

	// コンストラクタ
	MomentCanv(DirectX::SimpleMath::Vector2 screenRate);
	// デストラクタ
	~MomentCanv();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画関数
	void Draw(DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 origin, RECT_U rect);

private:

	// 最終座標
	static const DirectX::SimpleMath::Vector2 LAST_POSITION;
	// 画像の回転角度
	static const float LAST_ROTATE;
	// 移動・回転速度
	static const float SPEED_TO_LAST;
	// 画面外の座標
	static const DirectX::SimpleMath::Vector2 OUT_POSITION;

private:

	// スプライト描画
	std::unique_ptr<DrawSprite> m_sprite;
	// 座標
	DirectX::SimpleMath::Vector2 m_position;
	// 画面拡大率
	DirectX::SimpleMath::Vector2 m_screenRate;
	// 動作終了フラグ
	bool is_endMoving;
};

#endif // MOMENTCANV