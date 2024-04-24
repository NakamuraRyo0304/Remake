/*
 *	@File	IGameObject.h
 *	@Brief	ゲームオブジェクトのインターフェース。
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

// オブジェクトのステータス
#include "StatesList.h"

class IGameObject
{
public:

	// デストラクタ
	virtual ~IGameObject() = default;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

};

#endif // IGAMEOBJECT