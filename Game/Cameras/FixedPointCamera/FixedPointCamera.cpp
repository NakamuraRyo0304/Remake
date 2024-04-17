/*
 *	@File	FixedPointCamera.cpp
 *	@Brief	定点カメラ。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "FixedPointCamera.h"

// コンストラクタ
FixedPointCamera::FixedPointCamera(const SimpleMath::Vector2& screenSize)
	:
	IGameCamera(screenSize)			//基底クラス
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(0.0f, 2.0f, 24.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 12.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// デストラクタ
FixedPointCamera::~FixedPointCamera()
{
}

// 更新
void FixedPointCamera::Update()
{
	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
