/*
 *	@File	Editor.h
 *	@Brief	エディタ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITOR
#define EDITOR

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

//==============================================================================
// オブジェクトステータス
//==============================================================================
#include "Game/Common/IGameObject/IGameObjectStates.h"

class AdminCamera;
class BlockManager;
class EditorCollision;
class UI_Editor;
class Editor final : public IScene
{
private:

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;

	// ブロックマネージャ
	std::unique_ptr<BlockManager> m_blockManager;

	// UI
	std::unique_ptr<UI_Editor> m_ui;

	// エディタコリジョン
	std::unique_ptr<EditorCollision> m_editorCollision;

	// 描画するオブジェクトID
	ID m_selectionID;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Editor();
	~Editor();

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

private:

	/// <summary>
	/// コリジョン更新
	/// </summary>
	/// <param name="id">変更したいブロックのID</param>
	/// <returns>なし</returns>
	void UpdateCollisions(ID id);
};

#endif // Editor