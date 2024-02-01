/*
 *	@File	Coin.h
 *	@Brief	コインブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef COIN
#define COIN

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Coin : public IGameObject
{
private:

	// 衝突フラグ
	bool is_hit;

	// アクティブフラグ
	bool is_active;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Coin(DirectX::SimpleMath::Vector3 position);
	~Coin();

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

public:

	// アクティブフラグを取得
	bool IsActive() { return is_active; }
	// アクティブフラグを切り替える
	void SetActive(const bool flag) { is_active = flag; }

	// 衝突通知
	void SetHitFlag(bool isHit) { is_hit = isHit; }

};

#endif // COIN