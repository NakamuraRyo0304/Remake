/*
 *	@File	TitleScene.h
 *	@Brief	タイトルシーン。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TITLESCENE
#define	TITLESCENE

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky_Title;
class Bird_Title;
class UI_Title;
class Water;
class Logo;
class Timer;
class Iceberg;
class TitleScene final : public IScene
{
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

private:

	// ロゴのフェードイン速度
	static const float LOGO_FADE_IN_SPEED;

	// ロゴのフェードアウト速度
	static const float LOGO_FADE_OUT_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	TitleScene();
	~TitleScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize()                             override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update()                                 override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw()                                   override;
	/// <summary>
	/// 終了処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Finalize()                               override;
	/// <summary>
	/// 画面依存、デバイス依存の初期化
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateWDResources()                      override;

private:

	/// <summary>
	/// シーン内の変数初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void SetSceneValues()                         override;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <returns>なし</returns>
	void DebugDraw(DirectX::CommonStates& states) override;
};

#endif // TITLESCENE