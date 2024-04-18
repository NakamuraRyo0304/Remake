/*
 *	@File	SelectScene.h
 *	@Brief	セレクトシーン。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SELECTSCENE
#define SELECTSCENE

// 親シーンクラス
#include "Game/BaseScene/BaseScene.h"

class AdminCamera;
class BlockManager;
class UI_Select;
class Water;
class BG_Select;
class SelectScene final : public BaseScene
{
public:

	// ステージ番号を取得
	int GetSelectedNumber() const { return m_stageSelection; }
	// 最大ステージ番号を取得
	int GetMaxNumber() const { return MAX_SAMPLE_NUM; }

	// コンストラクタ
	SelectScene(const int& selection);
	// デストラクタ
	~SelectScene();
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
	// カメラの切り替え処理
	void ChangeAdminCamera();
	// シーン選択
	void SelectNext();

private:

	// サンプルステージ番号
	static const int MAX_SAMPLE_NUM = 4;
	// ０番はエディタの番号
	const int EDITOR_NUM = 0;

private:

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;
	// UI
	std::unique_ptr<UI_Select> m_ui;
	// ブロックマネージャ
	std::unique_ptr<BlockManager> m_stage[MAX_SAMPLE_NUM];
	// 水
	std::unique_ptr<Water> m_water;
	// 背景
	std::unique_ptr<BG_Select> m_backGround;
	// セレクト番号
	int m_stageSelection;

};

#endif // SELECTSCENE