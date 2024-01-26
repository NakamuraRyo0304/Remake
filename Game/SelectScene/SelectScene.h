/*
 *	@File	SelectScene.h
 *	@Brief	セレクトシーン。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SELECTSCENE
#define SELECTSCENE

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky_Select;
class UI_Select;
class Sand;

class SelectScene final : public IScene
{
private:

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;

	// UI
	std::unique_ptr<UI_Select> m_ui;

	// スカイ球
	std::unique_ptr<Sky_Select> m_sky;

	// セレクト番号
	int m_stageSelection;

	std::unique_ptr<Sand> m_sand;

private:

	// サンプルステージ番号
	static const int MAX_SAMPLE_NUM;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	SelectScene();
	~SelectScene();

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
	/// カメラの切り替え処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void ChangeAdminCamera();
};

#endif // SELECTSCENE