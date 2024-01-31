/*
 *	@File	EditorCollision.cpp
 *	@Brief	エディタの当たり判定。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Libraries/UserUtility.h"
#include "EditorCollision.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float EditorCollision::HIT_RADIUS = 1.0f;		// 当たり判定の半径

//==============================================================================
// コンストラクタ
//==============================================================================
EditorCollision::EditorCollision(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// ワールドマウス作成
	m_worldMouse = std::make_unique<WorldMouse>(view, proj);
}

//==============================================================================
// デストラクタ
//==============================================================================
EditorCollision::~EditorCollision()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void EditorCollision::Update(IGameObject* object, ID setting)
{
	auto _mouse = Mouse::Get().GetState();

	// ワールドマウスの更新
	m_worldMouse->Update();

	// nullだったら処理をしない
	if (UserUtility::IsNull(object)) return;

	// 当たり判定（球）
	if (UserUtility::CheckPointInSphere(m_worldMouse->GetPosition(), HIT_RADIUS, object->GetPosition()))
	{
		if (_mouse.leftButton)
		{
			object->SetID(setting);
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void EditorCollision::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// 描画関連処理
	m_worldMouse->Draw(view, proj);
}

//==============================================================================
// ワールドマウスの座標
//==============================================================================
SimpleMath::Vector3 EditorCollision::GetWorldMousePosition()
{
	return m_worldMouse->GetPosition();
}
