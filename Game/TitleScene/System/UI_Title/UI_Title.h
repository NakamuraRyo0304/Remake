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
public:

	// セレクトメニュー
	enum TitleSelect { Start, Exit };

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;

	// 座標
	std::map<const wchar_t*, DirectX::SimpleMath::Vector2> m_position;

	// 色
	std::map<const wchar_t*, DirectX::SimpleMath::Vector4> m_color;

	// 遷移先セレクト
	int m_selection;

	// 動作検知フラグ
	bool is_anything;

private:

	// 色変更速度
	static const float COLOR_SPEED;

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

	// セレクト番号を返す
	int GetSelection() const { return m_selection; }

	// 動作を検知状況を返す
	bool IsAnything() const { return is_anything; }
};

#endif // UI_TITLE