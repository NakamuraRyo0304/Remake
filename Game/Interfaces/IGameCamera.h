/*
 *	@File	IGameCamera.h
 *	@Brief	カメラのインターフェース。
 *	@Date	2023-11-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMECAMERA
#define IGAMECAMERA

class IGameCamera
{
public:

	// デストラクタ
	virtual ~IGameCamera() = default;
	// 更新
	virtual void Update() = 0;

};

#endif // IGAMECAMERA