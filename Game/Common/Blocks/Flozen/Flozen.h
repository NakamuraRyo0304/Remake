/*
 *	@File	Flozen.h
 *	@Brief	氷ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLOZEN
#define FLOZEN

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Flozen : public BaseObject
{
public:

	// コンストラクタ
	Flozen(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Flozen();

	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

};

#endif // FLOZEN