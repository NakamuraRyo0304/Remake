/*
 *  @File   BaseCamera.h
 *  @Brief  カメラの基底クラス。
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BASECAMERA
#define BASECAMERA

// インターフェース
#include "Game/Interfaces/IGameCamera.h"

class BaseCamera : public IGameCamera
{
public:

	// ビュー行列を取得
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	// ビュー行列を設定
	void SetView(const DirectX::SimpleMath::Matrix& view) { m_view = view; }
	// プロジェクション行列を取得
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	// プロジェクション行列を設定
	void SetProjection(const DirectX::SimpleMath::Matrix& proj) { m_projection = proj; }
	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// 上方向を取得
	const DirectX::SimpleMath::Vector3& GetUp() { return m_up; }
	// 注視点を取得
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	// 注視点を設定
	void SetTarget(const DirectX::SimpleMath::Vector3& target) { m_target = target; }
	// 初期位置を取得
	const DirectX::SimpleMath::Vector3& GetInitialPosition() { return m_initialPosition; }
	// 初期位置を設定
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }
	// 初期注視点を取得
	const DirectX::SimpleMath::Vector3& GetInitialTarget() { return m_initialTarget; }
	// 初期注視点を設定
	void SetInitialTarget(const DirectX::SimpleMath::Vector3& target) { m_initialTarget = target; }
	// ウィンドウサイズを取得
	const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_screenSize; }

	// コンストラクタ
	BaseCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~BaseCamera();

private:

	// プロジェクションを作成
	void CreateProjection();

private:

	// カメラの最近距離
	const float NEAR_PLANE = 0.1f;
	// カメラの最遠距離
	const float FAR_PLANE = 220.0f;
	// カメラアングル
	const float ANGLE = 45.0f;

private:

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;
	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 上方向
	DirectX::SimpleMath::Vector3 m_up;
	// 初期位置
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// 初期注視点
	DirectX::SimpleMath::Vector3 m_initialTarget;
	// スクリーンサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

};

#endif // BASECAMERA