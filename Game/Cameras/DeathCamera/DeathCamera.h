/*
 *	@File	DeathCamera.h
 *	@Brief	死亡時カメラ。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DEATHCAMERA
#define DEATHCAMERA

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

class DeathCamera : public IGameCamera
{
public:

	// コンストラクタ
	DeathCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~DeathCamera();
	// 更新
	void Update() override;

private:

	// 移動速度
	static const float MOVE_SPEED;

};

#endif // DEATHCAMERA