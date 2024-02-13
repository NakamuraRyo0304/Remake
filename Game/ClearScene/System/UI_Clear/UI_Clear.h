/*
 *	@File	UI_Clear.h
 *	@Brief	クリアUI。
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_CLEAR
#define UI_CLEAR

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Clear final : public IUserInterface
{
public:

	// 選択
	enum SELECT { NEXT, RESTART, STAGES, LENGTH };

	// スプライトに対応する構造体
	struct Option
	{
		DirectX::SimpleMath::Vector2 pos;
		DirectX::SimpleMath::Vector4 color;
	};

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;

	// オプション
	std::map<const wchar_t*, Option> m_options;

	// 選択
	SELECT m_select;

private:

	// 選択色
	static const DirectX::SimpleMath::Vector4 RED_COLOR;
	static const DirectX::SimpleMath::Vector4 BLACK_COLOR;

	// 色変更速度
	static const float COLOR_SPEED;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scS">画面サイズ</param>
	/// <param name="mscS">最大サイズ</param>
	/// <returns>なし</returns>
	UI_Clear(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Clear();

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

private:

	/// <summary>
	/// 色を変更する
	/// </summary>
	/// <param name="select">赤字にしたい文字</param>
	/// <returns>なし</returns>
	void ChangeColor(const SELECT& select);

public:

	// 次の操作を取得
	const SELECT& GetSelecion() { return m_select; }

	// 次の操作を設定
	void SetSelection(const SELECT& selection) { m_select = selection; }
};

#endif // UI_CLEAR