/*
 *	@File	RotateCamera.h
 *	@Brief	回転カメラ。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ROTATECAMERA
#define ROTATECAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class RotateCamera : public IGameCamera
{
private:

	// 操作する回転量
	float m_value;

private:

	// 回転範囲
	static const float ROTATE_RADIUS;

	// 増加量
	static const float INCREMENT_VALUE;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	RotateCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~RotateCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // ROTATECAMERA