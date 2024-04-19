/*
 *	@File	Editor.h
 *	@Brief	エディタ。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITOR
#define EDITOR

// 親シーンクラス
#include "Game/Bases/BaseScene.h"

// オブジェクトステータス
#include "Game/Interfaces/StatesList.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class EditorCollision;
class EditorGrids;
class UI_Editor;
class WorldMouse;
class Editor final : public BaseScene
{
public:

	// コンストラクタ
	Editor();
	// デストラクタ
	~Editor();
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
	// オブジェクトをセットする
	void SetDrawObject();
	// コリジョン更新
	void UpdateCollisions(ID id);

private:

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;
	// ブロックマネージャ
	std::unique_ptr<BlockManager> m_blockManager;
	// UI
	std::unique_ptr<UI_Editor> m_ui;
	// エディタコリジョン
	std::unique_ptr<EditorCollision> m_editorCollision;
	// ワールドマウス
	std::unique_ptr<WorldMouse> m_worldMouse;
	// カーソルオブジェクト
	std::unique_ptr<CursorObject> m_cursorObject;
	// エディタ用グリッド
	std::unique_ptr<EditorGrids> m_editorGrids;
	// 描画するオブジェクトID
	ID m_selectionID;

};

#endif // Editor