/*
 *	@File	DeathCamera.cpp
 *	@Brief	死亡時カメラ。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "DeathCamera.h"

// コンストラクタ
DeathCamera::DeathCamera(const SimpleMath::Vector2& screenSize)
	:
	BaseCamera(screenSize)			// 基底クラスのコンストラクタ
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(0.0f, -5.0f, 0.0f));
	SetTarget(SimpleMath::Vector3::Zero);
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

// デストラクタ
DeathCamera::~DeathCamera()
{
}

// 更新
void DeathCamera::Update()
{
    // ビュー行列をセット
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}