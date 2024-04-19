/*
 *	@File	FixedPointCamera.h
 *	@Brief	定点カメラ。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FIXEDPOINTCAMERA
#define FIXEDPOINTCAMERA

// 親カメラクラス
#include "Game/Bases/BaseCamera.h"

class FixedPointCamera : public BaseCamera
{
public:

	// コンストラクタ
	FixedPointCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~FixedPointCamera();
	// 更新
	void Update() override;
};

#endif // FIXEDPOINTCAMERA