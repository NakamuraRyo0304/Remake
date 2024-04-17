/*
 *	@File	UI_Title.h
 *	@Brief	タイトルUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_TITLE
#define UI_TITLE

 // 親シーンクラス
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Title final : public IUserInterface
{
public:

	// セレクト番号を返す
	int GetSelection() const { return m_selection; }

	// 動作を検知状況を返す
	bool IsAnything() const { return is_anything; }

	// コンストラクタ
	UI_Title(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~UI_Title();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

public:

	// セレクトメニュー
	enum TitleSelect { Start, Exit };

private:

	// 色変更速度
	static const float COLOR_SPEED;

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

};

#endif // UI_TITLE