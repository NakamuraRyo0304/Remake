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

class DrawSprite;
class ClearScene final : public IScene
{
private:

	// スプライト描画
	std::unique_ptr<DrawSprite> m_sprite;

private:

	// プレイシーンのスクショのオフセット値
	static const DirectX::SimpleMath::Vector2 PLAY_SC_OFFSET;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	ClearScene();
	~ClearScene();

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

#endif // CLEARSCENE