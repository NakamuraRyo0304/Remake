/*
 *	@File	Goal.h
 *	@Brief	ゴールオブジェクト。
 *	@Date	2024-02-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GOAL
#define GOAL

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Goal : public IGameObject
{
private:

	// 衝突フラグ
	bool is_hit;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Goal(DirectX::SimpleMath::Vector3 position);
	~Goal();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

public:

	// 衝突フラグをONにする(ゴール判定は１度のためONのみ)
	void OnHitFlag() { is_hit = true; }

	// フラグ取得
	bool IsHitFlag() const { return is_hit; }
};

#endif // GOAL