/*
 *	@File	FixedPointCamera.h
 *	@Brief	定点カメラ。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FIXEDPOINTCAMERA
#define FIXEDPOINTCAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class FixedPointCamera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	FixedPointCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~FixedPointCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // FIXEDPOINTCAMERA