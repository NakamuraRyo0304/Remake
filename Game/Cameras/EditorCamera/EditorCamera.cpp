/*
 *	@File	EditorCamera.cpp
 *	@Brief	エディタカメラ。
 *	@Date	2024-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "EditorCamera.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float EditorCamera::MOVE_SPEED = 0.02f;

//==============================================================================
// コンストラクタ
//==============================================================================
EditorCamera::EditorCamera(const SimpleMath::Vector2& screenSize)
	: IGameCamera(screenSize)
{
	// 座標と注視点をセット
	SetPosition(SimpleMath::Vector3(0.0f, 5.0f, 12.0f));
	SetTarget(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	// 初期状態を保持
	SetInitialPosition(GetPosition());
	SetInitialTarget(GetTarget());
}

//==============================================================================
// デストラクタ
//==============================================================================
EditorCamera::~EditorCamera()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void EditorCamera::Update()
{
    auto _key = Keyboard::Get().GetState();
    auto _forward = UserUtility::GetDirectionVector(GetPosition(), GetTarget());

    if (_key.W)
    {
        SetPosition(GetPosition() + _forward * MOVE_SPEED);
        SetTarget(GetTarget() + _forward * MOVE_SPEED);
    }
    if (_key.S)
    {
        SetPosition(GetPosition() - SimpleMath::Vector3::UnitZ * _forward * MOVE_SPEED);
        SetTarget(GetTarget() - SimpleMath::Vector3::UnitZ * _forward * MOVE_SPEED);
    }
    if (_key.D)
    {
        SetTarget(GetTarget() + SimpleMath::Vector3::UnitX * MOVE_SPEED * 2);
    }
    if (_key.A)
    {
        SetTarget(GetTarget() - SimpleMath::Vector3::UnitX * MOVE_SPEED * 2);
    }

    // ビュー行列をセット
    SetView(SimpleMath::Matrix::CreateLookAt(GetPosition(), GetTarget(), GetUp()));
}
