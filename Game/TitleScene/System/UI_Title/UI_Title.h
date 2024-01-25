/*
 *	@File	UI_Title.h
 *	@Brief	タイトルUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_TITLE
#define UI_TITLE

//==============================================================================
// 使用ファイルのインクルード
//==============================================================================
#include "Libraries/SystemDatas/Button/Button.h"

class UI_Title
{
private:

	// ボタン
	std::unique_ptr<Button> m_start;
	std::unique_ptr<Button> m_exit;

	// クリック判定
	bool is_startClick;
	bool is_exitClick;

private:

	// ホバー時のアルファ値
	static const float RELEASE_ALPHA;

	// アルファ値の動作速度
	static const float ALPHA_FADE_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenRatio">画面比率</param>
	/// <returns>なし</returns>
	UI_Title(DirectX::SimpleMath::Vector2 screenRatio);
	~UI_Title();

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

	// スタートボタンを押した
	const bool& IsClickStart() { return is_startClick; }
	// 終了ボタンを押した
	const bool& IsClickExit() { return is_exitClick; }
};

#endif // UI_TITLE