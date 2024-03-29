/*
 *  @File   ClearScene.h
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLEARSCENE
#define CLEARSCENE

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

class BG_Clear;
class MomentCanv;
class ScoreBoard;
class Timer;
class UI_Clear;
class Tape;
class Seal;
class ClearScene final : public IScene
{
private:

	// モーメントキャンバス
	std::unique_ptr<MomentCanv> m_momentCanv;

	// UI
	std::unique_ptr<UI_Clear> m_ui;

	// スコアボード
	std::unique_ptr<ScoreBoard> m_coinBoard, m_timeBoard;

	// ランダムカウント
	std::unique_ptr<Timer> m_direction;

	// バックグラウンド
	std::unique_ptr<BG_Clear> m_backGround;

	// テープ
	std::unique_ptr<Tape> m_tape[2];

	enum Sticker{ Coin, Clock, Length};
	// シール
	std::unique_ptr<Seal> m_seal[Sticker::Length];

	// クリア時間
	float m_clearTime;

	// 集めたコイン数/ステージ番号/最大ステージ番号
	int m_collectedCoin, m_stageNumber, m_maxNumber;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="time">クリアタイム</param>
	/// <param name="coins">コイン数</param>
	/// <param name="stage">ステージ番号</param>
	/// <param name="max">最大ステージ番号</param>
	/// <returns>なし</returns>
	ClearScene(float time, int coins, int stage, int max);
	~ClearScene();

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

public:

	// ステージ番号を取得する
	int GetStageNumber() const { return m_stageNumber; }

private:

	// シーン選択
	void SceneSelection();

};

#endif // CLEARSCENE