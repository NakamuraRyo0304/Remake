/*
 *	@File	UI_Select.h
 *	@Brief	セレクトUI。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_SELECT
#define UI_SELECT

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Select final : public IUserInterface
{
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;

	// 座標
	std::map<const wchar_t*, DirectX::SimpleMath::Vector2> m_position;

	// 色
	std::map<const wchar_t*, DirectX::SimpleMath::Vector4> m_color;

	// 選択ステージ番号
	int m_stageSelection;

	// ステージ画像アルファ値
	float m_stageAlpha;

private:

	// 色変更速度
	static const float COLOR_SPEED;

	// ステージ番号の間隔
	static const float STAGE_TEX_SPAN;

	// 画像の座標
	static const DirectX::SimpleMath::Vector2 STAGE_TEX_POS;

	// 画像の拡大率
	static const float STAGE_TEX_RATE;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scS">画面サイズ</param>
	/// <param name="mscS">最大サイズ</param>
	/// <returns>なし</returns>
	UI_Select(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Select();

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

	// 選択中のステージ番号を設定
	void SetSelectionNum(const int& num) { m_stageSelection = num; }

};

#endif // UI_SELECT