/*
 *	@File	DeathCamera.h
 *	@Brief	死亡時カメラ。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DEATHCAMERA
#define DEATHCAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class DeathCamera : public IGameCamera
{
private:

	// 移動速度
	static const float MOVE_SPEED;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	DeathCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~DeathCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;

};

#endif // DEATHCAMERA