/*
 *	@File	Lift.h
 *	@Brief	前後移動ブロック。
 *	@Date	2024-02-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LIFT
#define LIFT

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Lift : public BaseObject
{
public:

	// オフセットを取得
	float GetOffset() const { return m_offset; }

	// コンストラクタ
	Lift(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Lift();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 移動量
	float m_offset;

};

#endif // LIFT