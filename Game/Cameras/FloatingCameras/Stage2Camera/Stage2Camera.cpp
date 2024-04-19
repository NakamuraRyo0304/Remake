/*
 *	@File	Stage2Camera.cpp
 *	@Brief	ステージ２のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage2Camera.h"

// コンストラクタ
Stage2Camera::Stage2Camera(const SimpleMath::Vector2& screenSize)
	:
	BaseCamera(screenSize)		// 基底クラスのコンストラクタ
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(15.5f, 10.0f, 15.0f));
	SetTarget(SimpleMath::Vector3(15.5f, 5.0f, 7.5f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// デストラクタ
Stage2Camera::~Stage2Camera()
{
}

// 更新
void Stage2Camera::Update()
{
	// 浮遊している風の動き
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
