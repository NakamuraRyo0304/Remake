/*
 *	@File	Camera.cpp
 *	@Brief	カメラの設定。
 *	@Date	2023-04-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Camera.h"

//==============================================================================
// 定数の初期化
//==============================================================================
const float Camera::DEFAULT_CAMERA_DISTANCE = 20.0f;	// ターゲットからの距離
const float Camera::DEFAULT_CAMERA_SPEED = 0.05f;		// 移動速度
const float Camera::ARROW_SPEED = 0.01f;				// 矢印操作の速度
const int	Camera::MAX_SCROLL_VALUE = 2000;			// スクロール上限値
const int	Camera::MIN_SCROLL_VALUE = -1000;			// スクロール下限値
const float Camera::FAR_PLANE = 245.0f;					// 投影最遠値
const float Camera::NEAR_PLANE = 0.1f;					// 投影最近値
const float Camera::ANGLE_X_MAX = 45.5f;				// X軸回転の上限値
const float Camera::ANGLE_X_MIN = 44.0f;				// X軸回転の下限値

//==============================================================================
// コンストラクタ
//==============================================================================
Camera::Camera()
	: m_screenSize{}			// 画面のサイズ
	, m_angle{}					// 回転角
	, m_position{}				// 座標
	, m_addEye{}				// 目線の加算座標
	, m_addTarget{}				// 注視点の加算座標
	, m_prevMouse{}				// 過去のマウスの位置
	, m_scrollWheelValue{}		// マウスホイールの回転量
	, m_view{}					// ビュー行列
	, m_projection{}			// プロジェクション行列
	, m_rotateMatrix{}			// 回転量
	, is_allowMode{ false }		// カメラの視点移動フラグ(十字操作)
	, is_eagleMode{ false }		// カメラの視点移動フラグ(マウス操作)
	, is_zeroClamp{ false }		// マウスホイールのゼロクランプ
{
	// マウスの情報をリセット
	Mouse::Get().ResetScrollWheelValue();
	m_prevMouse.pos = SimpleMath::Vector2::Zero;
	m_prevMouse.wheel = 0;
	m_prevMouse.eagle = false;
}

//==============================================================================
// デストラクタ
//==============================================================================
Camera::~Camera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void Camera::Update()
{
	// キーボードのインスタンス取得
	auto _kb = Keyboard::Get().GetState();
	// マウスのインスタンス取得
	auto _ms = Mouse::Get().GetState();

	// マウスの左クリック＆ドラッグでカメラ座標を更新する
	if (_ms.leftButton)
	{
		// 視点移動しなければ処理しない
		if (not is_eagleMode) return;

		// マウスのドラッグによるカメラ移動
		DraggedDistance(_ms.x, _ms.y);
	}

	// マウスの座標を前回の値として保存
	m_prevMouse.pos.x = static_cast<float>(_ms.x); // X座標を保存
	m_prevMouse.pos.y = static_cast<float>(_ms.y); // Y座標を保存

	if (is_eagleMode)
	{
		m_scrollWheelValue = _ms.scrollWheelValue;
		if (m_scrollWheelValue > 0)
		{
			if (is_zeroClamp)
			{
				m_scrollWheelValue = 0;
				Mouse::Get().ResetScrollWheelValue();
			}
		}
	}

	// ビュー行列の算出
	CalculateViewMatrix();

	// 十字スイッチがオフなら動かさない
	if (not is_allowMode) return;

	// 移動量
	SimpleMath::Vector2 _moveVal = SimpleMath::Vector2::Zero;

	// 移動量を設定
	if (_kb.Right) { _moveVal.y =  ARROW_SPEED; }
	if (_kb.Left)  { _moveVal.y = -ARROW_SPEED; }
	if (_kb.Up)    { _moveVal.x =  ARROW_SPEED; }
	if (_kb.Down)  { _moveVal.x = -ARROW_SPEED; }

	// 角度変更
	m_angle += _moveVal;
}

//==============================================================================
// ドラッグした距離の計算
//==============================================================================
void Camera::DraggedDistance(int x, int y)
{
	// マウスポインタの前回からの変位
	// DEFAULT_CAMERA_SPEEDを乗算してドラッグの移動量を調整する
	float _dx = static_cast<float>(x - m_prevMouse.pos.x) * DEFAULT_CAMERA_SPEED;
	float _dy = static_cast<float>(y - m_prevMouse.pos.y) * DEFAULT_CAMERA_SPEED;

	if (_dx != 0.0f || _dy != 0.0f)
	{
		// マウスポインタの変位を元に、Ｘ軸Ｙ軸の回転角を求める
		float _angleX = _dy * XM_PI / 180.0f;
		float _angleY = _dx * XM_PI / 180.0f;

		// 角度の更新
		m_angle.x += _angleX;
		m_angle.y += _angleY;
	}
}

//==============================================================================
// プロジェクション行列の計算
//==============================================================================
const SimpleMath::Matrix& Camera::CreateProjection(SimpleMath::Vector2 size, float angle)
{
	// 画面サイズとアングルの保存
	m_screenSize = size;

	// 画角
	float _fieldOfView = XMConvertToRadians(angle);

	// 画面縦横比
	float _aspectRatio = size.x / size.y;

	// カメラから一番近い投影面
	float _nearPlane = NEAR_PLANE;

	// カメラから一番遠い投影面
	float _farPlane = FAR_PLANE;

	// カメラのレンズの作成
	SimpleMath::Matrix _projection =
		SimpleMath::Matrix::CreatePerspectiveFieldOfView(
			_fieldOfView, _aspectRatio, _nearPlane, _farPlane);

	// カメラ画角
	m_angle.x = angle;

	return m_projection = _projection;
}

//==============================================================================
// ビュー行列の計算
//==============================================================================
void Camera::CalculateViewMatrix()
{
	// ビュー行列を算出する
	SimpleMath::Matrix _rotY = SimpleMath::Matrix::CreateRotationY(m_angle.y);
	SimpleMath::Matrix _rotX = SimpleMath::Matrix::CreateRotationX(m_angle.x);

	// 回転量を計算
	SimpleMath::Matrix _rt = _rotY * _rotX;
	m_rotateMatrix = _rt;

	// ポジション
	SimpleMath::Vector3    _eye(0.0f, 0.1f, 1.0f);

	// カメラの傾き（目線の角度)
	SimpleMath::Vector3     _up(0.0f, 1.0f, 0.0f);
	SimpleMath::Vector3 _target(0.0f, 0.0f, 0.0f);

	_eye = SimpleMath::Vector3::Transform(_eye, _rt.Invert());
	_eye *= (DEFAULT_CAMERA_DISTANCE - static_cast<float>(m_scrollWheelValue / 100));
	_up  = SimpleMath::Vector3::Transform(_up,  _rt.Invert());

	// デフォルトの初期位置
	m_position = _eye + m_addEye;
	m_target = _target + m_addTarget;
	m_view = SimpleMath::Matrix::CreateLookAt(m_position, m_target, _up);
}