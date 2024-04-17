/*
 *	@File	EditorCollision.cpp
 *	@Brief	エディタの当たり判定。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "EditorCollision.h"

// 定数の設定
const float EditorCollision::HIT_RADIUS = 0.5f;		// 当たり判定の半径

// コンストラクタ
EditorCollision::EditorCollision()
	:
	m_position()									// 座標
{
}

// デストラクタ
EditorCollision::~EditorCollision()
{
}

// 更新
void EditorCollision::Update(IGameObject* object, ID setting)
{
	auto ms = Mouse::Get().GetState();

	// nullだったら処理をしない
	if (UserUtility::IsNull(object)) return;

	// 当たり判定（球）
	if (UserUtility::CheckPointInSphere(m_position, HIT_RADIUS, object->GetPosition()))
	{
		if (ms.leftButton)
		{
			object->SetID(setting);
		}
	}
}