/*
 *  @File   Island.h
 *  @Brief  孤島。
 *  @Date   2024-02-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISLAND
#define ISLAND

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class Island : public IGameObject
{
public:

	// コンストラクタ
	Island(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	// デストラクタ
	~Island();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;
private:

	// 回転量
	float m_rotation;
	// 回転速度
	float m_speed;

};

#endif // ISLAND