/*
 *	@File	EditorCamera.h
 *	@Brief	エディタカメラ。
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCAMERA
#define EDITORCAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

class EditorCamera : public IGameCamera
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
	EditorCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~EditorCamera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // EDITORCAMERA