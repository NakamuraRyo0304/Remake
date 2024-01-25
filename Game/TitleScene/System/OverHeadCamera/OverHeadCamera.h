/*
 *	@File	OverHeadCamera.h
 *	@Brief	俯瞰カメラ。
 *	@Date	2023-12-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef OVERHEADCAMERA
#define OVERHEADCAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class OverHeadCamera : public IGameCamera
{
private:

	// 上下移動の幅
	static const float AXIS_Y_WIDTH;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	OverHeadCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~OverHeadCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // OVERHEADCAMERA