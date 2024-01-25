/*
 *	@File	Camera.h
 *	@Brief	カメラの設定。
 *	@Date	2023-04-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CAMERA
#define CAMERA

class Camera
{
public:
	// スクリーンサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

public:
	static const float DEFAULT_CAMERA_DISTANCE;	// ターゲットからの距離
	static const float DEFAULT_CAMERA_SPEED;	// 移動速度
	static const float ARROW_SPEED;				// 矢印操作の速度
	static const int MAX_SCROLL_VALUE;			// スクロール上限値
	static const int MIN_SCROLL_VALUE;			// スクロール下限値
	static const float FAR_PLANE;				// 投影最遠値
	static const float NEAR_PLANE;				// 投影最近値
	static const float ANGLE_X_MAX;				// X軸回転の上限値
	static const float ANGLE_X_MIN;				// X軸回転の下限値

private:

	// スクリーン座標、ホイール値、モード
	struct PrevMouse { DirectX::SimpleMath::Vector2 pos; int wheel; bool eagle; };

	// 前回のマウス情報
	PrevMouse m_prevMouse;

	// マウスホイールのスクロール値
	int m_scrollWheelValue;

	// 回転角
	DirectX::SimpleMath::Vector2 m_angle;

	// ビュー行列/プロジェクション行列/回転行列
	DirectX::SimpleMath::Matrix m_view, m_projection, m_rotateMatrix;

	// カメラの座標/加算値
	DirectX::SimpleMath::Vector3 m_position, m_addEye;

	// 注視点/加算値
	DirectX::SimpleMath::Vector3 m_target, m_addTarget;

	// 視点移動モード
	bool is_eagleMode, is_allowMode, is_zeroClamp;

public:
	Camera();
	~Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

private:
	/// <summary>
	/// マウスのドラッグした距離を計算
	/// </summary>
	/// <param name="x">スクリーン座標X</param>
	/// <param name="y">スクリーン座標Y</param>
	/// <returns>なし</returns>
	void DraggedDistance(int x, int y);

	/// <summary>
	/// ビュー行列の計算
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CalculateViewMatrix();

//--------------------------------------------------------//
//アクセサ                                                //
//--------------------------------------------------------//
public:
	/// <summary>
	/// 射影行列を作成
	/// </summary>
	/// <param name="size">画面サイズ</param>
	/// <param name="angle">カメラ画角</param>
	/// <returns>射影行列</returns>
	const DirectX::SimpleMath::Matrix& CreateProjection(DirectX::SimpleMath::Vector2 size,float angle = 45.0f);
	/// <summary>
	/// ビュー行列を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>ビュー行列</returns>
	const DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	/// <summary>
	/// プロジェクション行列を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>プロジェクション行列</returns>
	const DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	/// <summary>
	/// カメラの位置を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>カメラの位置</returns>
	const DirectX::SimpleMath::Vector3& GetEyePosition() { return m_addEye; }
	/// <summary>
	/// ターゲットの位置を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>ターゲットの位置</returns>
	const DirectX::SimpleMath::Vector3& GetTargetPosition() { return m_target; }
	/// <summary>
	/// カメラの位置を加算
	/// </summary>
	/// <param name="pos">加算座標</param>
	/// <returns>なし</returns>
	void AddEyePosition(const DirectX::SimpleMath::Vector3& pos) { m_addEye = pos; }
	/// <summary>
	/// カメラの注視点の位置を加算
	/// </summary>
	/// <param name="pos">加算座標</param>
	/// <returns>なし</returns>
	void AddTargetPosition(const DirectX::SimpleMath::Vector3& pos) { m_addTarget = pos; }
	/// <summary>
	/// カメラの角度を設定
	/// </summary>
	/// <param name="angle">角度</param>
	/// <returns>なし</returns>
	void SetCameraAngle(const DirectX::SimpleMath::Vector2& angle) { m_angle = angle; }
	/// <summary>
	/// マウス操作の有効化
	/// </summary>
	/// <param name="flag">使用時にTrue</param>
	/// <returns>カメラがマウス操作可能になる</returns>
	void SetEagleMode(const bool& flag = true) { is_eagleMode = flag; }
	/// <summary>
	/// 十字キー操作の有効化
	/// </summary>
	/// <param name="flag">使用時にTrue</param>
	/// <returns>カメラが十字キー操作可能になる</returns>
	void SetArrowMode(const bool& flag = true) { is_allowMode = flag; }
	/// <summary>
	/// マウスのゼロクランプの切り替え
	/// </summary>
	/// <param name="flag">使用時にTrue</param>
	/// <returns>マウスホイールが0未満で0に切りあがる</returns>
	void IsZeroClamp(const bool& flag = true) { is_zeroClamp = flag; }

};

#endif // CAMERA
