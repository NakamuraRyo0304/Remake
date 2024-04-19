/*
 *  @File   ClearScene.h
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLEARSCENE
#define CLEARSCENE

// 親シーンクラス
#include "Game/Bases/BaseScene.h"

class BG_Clear;
class MomentCanv;
class ScoreBoard;
class Timer;
class UI_Clear;
class Tape;
class Seal;
class ClearScene final : public BaseScene
{
public:

	// ステージ番号を取得する
	int GetStageNumber() const { return m_stageNumber; }

	// コンストラクタ
	ClearScene(float time, int coins, int stage, int max);
	// デストラクタ
	~ClearScene();
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

	// シーン内の変数初期化
	void SetSceneValues() override;
	// デバッグ描画
	void DebugDraw(DirectX::CommonStates& states) override;
	// シーン選択
	void SceneSelection();

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
	enum Sticker { Coin, Clock, Length };
	// シール
	std::unique_ptr<Seal> m_seal[Sticker::Length];
	// クリア時間
	float m_clearTime;
	// 集めたコイン数/ステージ番号/最大ステージ番号
	int m_collectedCoin, m_stageNumber, m_maxNumber;

};

#endif // CLEARSCENE