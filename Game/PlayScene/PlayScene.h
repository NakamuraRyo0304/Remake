/*
 *	@File	PlayScene.h
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYSCENE
#define	PLAYSCENE

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky_Play;
class Player;
class WorldMouse;
class PlayScene final : public IScene
{
private:

	// ステージ番号
	int m_stageNumber;

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;

	// スカイ球
	std::unique_ptr<Sky_Play> m_sky;

	// プレイヤー
	std::unique_ptr<Player> m_player;

	// ワールドマウス
	std::unique_ptr<WorldMouse> m_worldMouse;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="number">ステージ番号</param>
	/// <returns>なし</returns>
	PlayScene(const int& number);
	~PlayScene();

	/// <summary>
	/// 初期化処理
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
	/// <summary>
	/// 終了処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Finalize() override;
	/// <summary>
	/// 画面依存、デバイス依存の初期化
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateWDResources() override;

private:

	/// <summary>
	/// シーン内の変数初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void SetSceneValues() override;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <returns>なし</returns>
	void DebugDraw(DirectX::CommonStates& states) override;
};

#endif // PlayScene