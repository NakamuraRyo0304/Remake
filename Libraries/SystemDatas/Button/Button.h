/*
 *	@File	Button.h
 *	@Brief	マウスクリックで動作するボタン。
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BUTTON
#define BUTTON

//==============================================================================
// スプライト描画クラスをインクルード
//==============================================================================
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

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

	// ボタン名
	const wchar_t* m_name;

	// 座標
	DirectX::SimpleMath::Vector2 m_position;

	// 補正座標
	DirectX::SimpleMath::Vector2 m_correctionPosition;

	// 色
	DirectX::SimpleMath::Color m_color;

	// サイズ
	RECT_U m_size;

	// 中心座標
	DirectX::SimpleMath::Vector2 m_origin;

	// 拡大率
	DirectX::SimpleMath::Vector2 m_rate;

	// 状態
	State m_states;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="name">ボタン名</param>
	/// <param name="image">画像パス</param>
	/// <returns>なし</returns>
	Button(const wchar_t* name,const wchar_t* image);
	~Button();

	/// <summary>
	/// 初期設定
	/// </summary>
	/// <param name="position">左上座標</param>
	/// <param name="rate">拡大率</param>
	/// <param name="rect">画像サイズ</param>
	/// <param name="screenRatio">画面比率</param>
	/// <param name="color">色指定</param>
	/// <returns>なし</returns>
	void Initialize(DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 rate,
		RECT_U rect,	DirectX::SimpleMath::Vector2 screenRatio, DirectX::XMVECTORF32 color = { 1,1,1,1 });

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();

	// ボタンの状態を取得
	const State& GetState() { return m_states; }

	// 拡大率を設定
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }

	// 補正座標を設定
	void SetCorrectionPosition(const DirectX::SimpleMath::Vector2& pos) { m_correctionPosition = pos; }

private:

	/// <summary>
	/// ボタンの状態を変更
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void ChangeButton();

};

#endif // BUTTON