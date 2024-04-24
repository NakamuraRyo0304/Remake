/*
 *	@File	UI_Select.h
 *	@Brief	セレクトUI。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_SELECT
#define UI_SELECT

// 親シーンクラス
#include "Game/Bases/BaseUI.h"

class UI_Select final : public BaseUI
{
public:

	// 選択中のステージ番号を設定
	void SetSelectionNum(const int& num) { m_selection = num; }

	// コンストラクタ
	UI_Select(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~UI_Select();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

private:

	// 色変更速度
	static const float COLOR_SPEED;
	// ステージ番号の間隔
	static const float STAGE_TEX_SPAN;
	// 画像の座標
	static const DirectX::SimpleMath::Vector2 STAGE_TEX_POS;
	// 画像の拡大率
	static const float STAGE_TEX_RATE;
	// エディタ文字切り取り位置
	const RECT_U RECT_EDIT = RECT_U(0, 0, 768, 128);
	// ステージ文字切り取り位置
	const RECT_U RECT_GAME = RECT_U(0, 0, 382, 128);

private:

	// 色リセット関数
	void ResetColors();

	//

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;
	// 座標
	std::map<std::wstring, DirectX::SimpleMath::Vector2> m_position;
	// 色
	std::map<std::wstring, DirectX::SimpleMath::Vector4> m_color;
	// 選択ステージ番号
	int m_selection;
	// ステージ画像アルファ値
	float m_stageAlpha;

};

#endif // UI_SELECT