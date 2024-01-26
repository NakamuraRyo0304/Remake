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
	SetPosition(SimpleMath::Vector3(0.0f, 30.0f, 0.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
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
	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
