/*
 *	@File	Stage0Camera.cpp
 *	@Brief	ステージ０（エディタ）のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage0Camera.h"

// コンストラクタ
Stage0Camera::Stage0Camera(const SimpleMath::Vector2& screenSize)
	:
	BaseCamera(screenSize)		// 基底クラスのコンストラクタ
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(10.0f, 30.0f, 10.0f));
	SetTarget(SimpleMath::Vector3(10.0f, 0.0f, 0.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// デストラクタ
Stage0Camera::~Stage0Camera()
{
}

// 更新
void Stage0Camera::Update()
{
	// 浮遊している風の動き
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
