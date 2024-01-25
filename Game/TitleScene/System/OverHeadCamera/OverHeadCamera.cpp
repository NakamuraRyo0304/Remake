/*
 *	@File	OverHeadCamera.cpp
 *	@Brief	俯瞰カメラ。
 *	@Date	2023-12-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "OverHeadCamera.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float OverHeadCamera::AXIS_Y_WIDTH = 3.0f;	// Y軸移動

//==============================================================================
// コンストラクタ
//==============================================================================
OverHeadCamera::OverHeadCamera(const SimpleMath::Vector2& screenSize)
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
OverHeadCamera::~OverHeadCamera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void OverHeadCamera::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 座標をセット
	SetPosition(SimpleMath::Vector3(
		GetPosition().x,
		GetInitialPosition().y + sinf(_timer) * AXIS_Y_WIDTH,
		GetPosition().z)
	);

	// ビュー行列をセット
	SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
