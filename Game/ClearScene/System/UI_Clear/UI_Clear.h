/*
 *	@File	UI_Clear.h
 *	@Brief	クリアUI。
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_CLEAR
#define UI_CLEAR

// 親シーンクラス
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Clear final : public IUserInterface
{
public:

	// 選択の種類
	enum SELECT { NEXT, RESTART, STAGES, LENGTH };

	// スプライトに対応する構造体
	struct Option
	{
		DirectX::SimpleMath::Vector2 pos;
		DirectX::SimpleMath::Vector4 color;
	};

public:

	// 次の操作を取得
	SELECT GetSelecion() const { return m_select; }
	// 次の操作を設定
	void SetSelection(const SELECT& selection) { m_select = selection; }

	// 動作の終了状況を取得する
	bool IsEndMoving() const { return is_endMoving; }

	// コンストラクタ
	UI_Clear(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~UI_Clear();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:

	// 色変更速度
	static const float COLOR_SPEED;
	// 最終X座標
	static const float LAST_POS_X;

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;
	// オプション
	std::map<const wchar_t*, Option> m_options;
	// 選択
	SELECT m_select;
	// 動作終了フラグ
	bool is_endMoving;

private:

	/// <summary>
	/// 色を変更する
	/// </summary>
	/// <param name="select">赤字にしたい文字</param>
	/// <returns>なし</returns>
	void ChangeColor(const SELECT& select);

};

#endif // UI_CLEAR