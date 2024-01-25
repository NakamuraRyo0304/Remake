/*
 *	@File	Bird_Title.h
 *	@Brief	タイトルに表示するトリ。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BIRD_TITLE
#define BIRD_TITLE

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Bird_Title : public IGameObject
{
private:

	// 再スタートライン
	static const float RESTART_LINE;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Bird_Title();
	~Bird_Title();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) override;

private:

	/// <summary>
	/// ランダムでX座標を再抽選する
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void RandomXPosition();
};

#endif // STAGE_TITLE