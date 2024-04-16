/*
 *	@File	Stage1Camera.cpp
 *	@Brief	ステージ１のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage1Camera.h"

// コンストラクタ
Stage1Camera::Stage1Camera(const SimpleMath::Vector2& screenSize)
	:
	IGameCamera(screenSize)			// 基底クラス
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(3.5f, 10.0f, 15.0f));
	SetTarget(SimpleMath::Vector3(3.5f, 5.0f, 7.5f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// デストラクタ
Stage1Camera::~Stage1Camera()
{
}

// 更新
void Stage1Camera::Update()
{
	// 浮遊している風の動き
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(timer));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
