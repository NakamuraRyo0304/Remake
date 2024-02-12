/*
 *	@File	Stage4Camera.cpp
 *	@Brief	ステージ４のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage4Camera.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Stage4Camera::Stage4Camera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(3.5f, 10.0f, 5.5f));
	SetTarget(SimpleMath::Vector3(3.5f, 5.0f, -2.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// デストラクタ
//==============================================================================
Stage4Camera::~Stage4Camera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void Stage4Camera::Update()
{
	// 浮遊している風の動き
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitY * sinf(_timer));

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
