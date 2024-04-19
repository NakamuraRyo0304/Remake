/*
 *	@File	Spike.h
 *	@Brief	棘オブジェクト(敵)。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SPIKE
#define SPIKE

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Spike : public BaseObject
{
public:

	// 衝突通知を取得
	bool IsHitFlag() const { return is_hit; }
	// 衝突通知
	void SetHitFlag(bool isHit) { is_hit = isHit; }

	// コンストラクタ
	Spike(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Spike();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 捕食回転速度
	static const float EATING_SPEED;

private:

	// 衝突フラグ
	bool is_hit;
};

#endif // SPIKE