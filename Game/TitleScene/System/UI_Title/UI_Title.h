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
 // 親シーンクラス
 //==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Title final : public IUserInterface
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
	/// <param name="scS">画面サイズ</param>
	/// <param name="mscS">最大サイズ</param>
	/// <returns>なし</returns>
	UI_Title(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Title();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw() override;

public:

	// スタートボタンを押した
	const bool& IsClickStart() { return is_startClick; }
	// 終了ボタンを押した
	const bool& IsClickExit() { return is_exitClick; }
};

#endif // UI_TITLE