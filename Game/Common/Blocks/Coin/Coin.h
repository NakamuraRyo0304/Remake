/*
 *	@File	Coin.h
 *	@Brief	コインブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef COIN
#define COIN

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Coin : public BaseObject
{
public:

	// 衝突通知を取得
	bool IsHit() const { return is_hit; }
	// 衝突通知を設定
	void SetHitFlag(bool isHit) { is_hit = isHit; }

	// コンストラクタ
	Coin(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Coin();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 回転速度
	static const float ROTATE_SPEED;

private:

	// 衝突フラグ
	bool is_hit;

};

#endif // COIN