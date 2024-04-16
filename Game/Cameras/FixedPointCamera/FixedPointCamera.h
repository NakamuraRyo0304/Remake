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
#include "Game/Common/IGameCamera/IGameCamera.h"

class FixedPointCamera : public IGameCamera
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