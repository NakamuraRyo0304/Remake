/*
 *	@File	UI_Editor.h
 *	@Brief	エディタUI。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_EDITOR
#define UI_EDITOR

// 親シーンクラス
#include "Game/Common/IUserInterface/IUserInterface.h"

class DrawKeys;
class UI_Editor final : public IUserInterface
{
public:

	// ボタンの名前
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

		Length_bn
	};

	// キーの名前
	enum KEY_NAME
	{
		WKEY,
		SKEY,
		AKEY,
		DKEY,

		Length__key
	};

public:

	// ボタンのクリック状況を取得
	bool IsClickButton(BUTTON_NAME name) const { return is_clicks[name]; }
	// ボタンの加算座標を返す
	const DirectX::SimpleMath::Vector2& GetAddPosition();

	// コンストラクタ
	UI_Editor(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~UI_Editor();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:

	// ボタンの位置調整
	void MoveButtonPosition();

private:

	// ボタン
	std::vector<std::unique_ptr<Button>> m_buttons;
	// キー
	std::map<KEY_NAME, std::unique_ptr<DrawKeys>> m_keys;
	// クリックフラグ
	bool is_clicks[BUTTON_NAME::Length_bn];
	// ボタンを画面外に隠すフラグ
	bool is_blindFlag;

};

#endif // UI_EDITOR