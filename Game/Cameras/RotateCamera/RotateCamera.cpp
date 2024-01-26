/*
 *	@File	RotateCamera.cpp
 *	@Brief	回転カメラ。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "RotateCamera.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float RotateCamera::ROTATE_RADIUS = 15.0f;	// 回転範囲
const float RotateCamera::INCREMENT_VALUE = 0.1f;	// 増加量

//==============================================================================
// コンストラクタ
//==============================================================================
RotateCamera::RotateCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
	, m_value{ 0.0f }			// 操作する値
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(0.0f, 10.0f, 0.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// デストラクタ
//==============================================================================
RotateCamera::~RotateCamera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void RotateCamera::Update()
{
	auto _key = Keyboard::Get().GetState();

	if (_key.Left) { m_value -= INCREMENT_VALUE; }
	if (_key.Right) { m_value += INCREMENT_VALUE; }

	// 回転量を保存
	float _x = cosf(m_value) - sinf(m_value);
	float _z = sinf(m_value) + cosf(m_value);
	_x *= ROTATE_RADIUS;
	_z *= ROTATE_RADIUS;

	// 座標の設定
	SetPosition(SimpleMath::Vector3(_x, GetPosition().y, _z));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
