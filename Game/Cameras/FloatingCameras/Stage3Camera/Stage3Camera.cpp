/*
 *	@File	Stage3Camera.cpp
 *	@Brief	ステージ３のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage3Camera.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Stage3Camera::Stage3Camera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(0.0f, 5.0f, 10.0f));
	SetTarget(SimpleMath::Vector3(10.0f, 5.0f, 0.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// デストラクタ
//==============================================================================
Stage3Camera::~Stage3Camera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void Stage3Camera::Update()
{
	// 浮遊している風の動き
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(_timer));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
