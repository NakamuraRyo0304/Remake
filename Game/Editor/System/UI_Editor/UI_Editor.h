/*
 *	@File	UI_Editor.h
 *	@Brief	エディタUI。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_EDITOR
#define UI_EDITOR

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Editor final : public IUserInterface
{
public:

	enum BUTTON_NAME
	{
		LoadFile,
		WriteFile,
		Flozen_bn,
		Cloud_bn,
		Coin_bn,
		Air_bn,
		Player_bn,
		Goal_bn,
		OC1_bn,
		OC2_bn,
		Spike_bn,
		Lift_bn,

		Length
	};


private:

	// フラグ
	bool is_clicks[BUTTON_NAME::Length];

	// ボタン
	std::vector<std::unique_ptr<Button>> m_buttons;

	// ボタンを画面外に隠すフラグ
	bool is_blindFlag;


public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scS">画面サイズ</param>
	/// <param name="mscS">最大サイズ</param>
	/// <returns>なし</returns>
	UI_Editor(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Editor();

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

	// ボタンのクリック状況を取得
	const bool& IsClickButton(BUTTON_NAME name) { return is_clicks[name]; }

	// ボタンの加算座標を返す
	const DirectX::SimpleMath::Vector2& GetAddPosition();

private:

	// ボタンの位置調整
	void MoveButtonPosition();

};

#endif // UI_EDITOR