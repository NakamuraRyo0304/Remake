/*
 *	@File	EditorCamera.h
 *	@Brief	エディタカメラ。
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCAMERA
#define EDITORCAMERA

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

class EditorCamera : public IGameCamera
{
public:

	// コンストラクタ
	EditorCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~EditorCamera();
	// 更新
	void Update() override;

private:

	// 視点番号
	enum class ViewPoint
	{
		PointFront,		// 前方位置
		PointRight,		// 右側位置
		PointBack,		// 後方位置
		PointLeft,		// 左側位置

		Length,			// 全要素数
	};

	// 移動速度
	static const float MOVE_SPEED;
	// 最高高度
	static const float MAX_HEIGHT;

private:

	// カメラの位置を更新
	void UpdateViewPoint();

private:

	// ビューポイントを格納する変数
	ViewPoint m_viewPoint;
	// 目的ポイント
	DirectX::SimpleMath::Vector3 m_viewPosition;
	// 注視点ポイント
	DirectX::SimpleMath::Vector3 m_viewTarget;

};

#endif // EDITORCAMERA