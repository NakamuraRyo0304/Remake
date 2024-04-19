/*
 *	@File	Goal.h
 *	@Brief	ゴールオブジェクト。
 *	@Date	2024-02-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GOAL
#define GOAL

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Goal : public BaseObject
{
public:

	// 衝突フラグをONにする(ゴール判定は１度のためONのみ)
	void OnHitFlag() { is_hit = true; }
	// フラグ取得
	bool IsHitFlag() const { return is_hit; }

	// コンストラクタ
	Goal(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Goal();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 衝突フラグ
	bool is_hit;

};

#endif // GOAL