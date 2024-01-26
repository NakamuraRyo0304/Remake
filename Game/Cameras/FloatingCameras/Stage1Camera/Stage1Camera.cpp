/*
 *	@File	Stage1Camera.cpp
 *	@Brief	ステージ１のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Stage1Camera.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Stage1Camera::Stage1Camera(const SimpleMath::Vector2& screenSize)
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
Stage1Camera::~Stage1Camera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void Stage1Camera::Update()
{
	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
