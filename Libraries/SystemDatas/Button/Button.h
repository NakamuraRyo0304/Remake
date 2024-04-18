/*
 *	@File	Button.h
 *	@Brief	マウスクリックで動作するボタン。
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BUTTON
#define BUTTON

// スプライト描画クラスをインクルード
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class Button
{
public:

	// ボタンの状態
	enum class State
	{
		Release,	// 離れている状態
		Hover,		// 重なっている状態
		Push,		// 押している状態
		Length,		// 要素数
	};

public:

	// ボタンの状態を取得
	State GetState() const { return m_states; }
	// 拡大率を設定
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// 元の拡大率を取得
	const DirectX::SimpleMath::Vector2& GetBaseRate() { return m_baseRate; }
	// 色を取得
	const DirectX::SimpleMath::Color& GetColor() { return m_color; }
	// 色を設定
	void SetColor(const DirectX::SimpleMath::Color& color) { m_color = color; }
	// 移動座標を取得
	const DirectX::SimpleMath::Vector2& GetAdderPosition() { return m_adder; }
	// 移動座標を設定
	void SetAdderPosition(const DirectX::SimpleMath::Vector2 pos) { m_adder = pos; }

	// コンストラクタ
	Button(const wchar_t* name,const wchar_t* image);
	// デストラクタ
	~Button();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 rate,
		RECT_U rect, DirectX::SimpleMath::Vector2 screenRatio, DirectX::XMVECTORF32 color = { 1,1,1,1 });
	// 更新
	void Update();
	// 描画
	void Draw();

private:

	// サイズ
	RECT_U m_size;
	// 状態
	State m_states;
	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;
	// ボタン名
	const wchar_t* m_name;
	// 座標・加算座標・中心座標
	DirectX::SimpleMath::Vector2 m_position, m_adder, m_origin;
	// 色
	DirectX::SimpleMath::Color m_color;
	// 拡大率・元の拡大率・スクリーン倍率
	DirectX::SimpleMath::Vector2 m_rate, m_baseRate, m_screenRate;

};

#endif // BUTTON