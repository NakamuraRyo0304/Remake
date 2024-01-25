/*
 *	@File	NewCamera.h
 *	@Brief	カメラの新規改造クラス。
 *	@Date	2024-01-20
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef NEWCAMERA
#define NEWCAMERA

class NewCamera
{
private:

	// 行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// カメラの位置
	DirectX::SimpleMath::Vector3 m_position;

	// カメラの注視点
	DirectX::SimpleMath::Vector3 m_targetPosition;

	// カメラの上方向
	DirectX::SimpleMath::Vector3 m_upDirection;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	NewCamera();
	~NewCamera();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="target">注視点</param>
	/// <param name="angle">画角</param>
	/// <param name="aspect">画面アスペクト比</param>
	/// <param name="nearClip">最も近い距離</param>
	/// <param name="farClip">最も遠い距離</param>
	/// <returns>なし</returns>
	void Initialize(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 target,
		float angle,float aspect, float nearClip, float farClip);
};

#endif // NEWCAMERA
