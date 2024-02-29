/*
 *	@File	Spike.h
 *	@Brief	棘オブジェクト(敵)。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SPIKE
#define SPIKE

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Spike : public IGameObject
{
private:

	// 衝突フラグ
	bool is_hit;
private:

	// 捕食回転速度
	static const float EATING_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Spike(DirectX::SimpleMath::Vector3 position);
	~Spike();

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

	// 衝突通知を取得
	bool IsHitFlag() const { return is_hit; }
	// 衝突通知
	void SetHitFlag(bool isHit) { is_hit = isHit; }

};

#endif // SPIKE