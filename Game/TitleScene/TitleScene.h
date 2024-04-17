/*
 *	@File	TitleScene.h
 *	@Brief	タイトルシーン。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TITLESCENE
#define	TITLESCENE

// 親シーンクラス
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky_Title;
class Bird_Title;
class UI_Title;
class Water;
class Logo;
class Timer;
class Iceberg;
class Island;
class MoveMonitor;
class TitleScene final : public IScene
{
public:

	// コンストラクタ
	TitleScene();
	// デンストラクタ
	~TitleScene();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// 終了
	void Finalize() override;
	// 画面依存、デバイス依存の初期化
	void CreateWDResources() override;

private:

	// ロゴのフェードイン速度
	static const float LOGO_FADE_IN_SPEED;
	// ロゴのフェードアウト速度
	static const float LOGO_FADE_OUT_SPEED;
	// ４分の１
	const float QUARTER = 0.25f;

private:

	// シーン内の変数初期化関数
	void SetSceneValues() override;
	// デバッグ描画
	void DebugDraw(DirectX::CommonStates& states) override;

private:

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;
	// UI
	std::unique_ptr<UI_Title> m_ui;
	// スカイ球
	std::unique_ptr<Sky_Title> m_sky;
	// トリ
	std::unique_ptr<Bird_Title> m_birdTitle;
	// 水
	std::unique_ptr<Water> m_water;
	// タイトルロゴ
	std::unique_ptr<Logo> m_logo;
	// タイマー
	std::unique_ptr<Timer> m_timer;
	// 氷山
	std::unique_ptr<Iceberg> m_iceberg;
	// 孤島
	std::unique_ptr<Island> m_island;
	// モニター監視者
	std::unique_ptr<MoveMonitor> m_moveMonitor;

};

#endif // TITLESCENE