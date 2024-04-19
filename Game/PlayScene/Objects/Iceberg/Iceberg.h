/*
 *  @File   Iceberg.h
 *  @Brief  氷山。
 *  @Date   2024-02-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ICEBERG
#define ICEBERG

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Iceberg : public BaseObject
{
public:

	// コンストラクタ
	Iceberg(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	// デストラクタ
	~Iceberg();
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

#endif // ICEBERG