/*
 *	@File	EditorCollision.h
 *	@Brief	エディタの当たり判定。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCOLLISION
#define EDITORCOLLISION

// ブロックマネージャ
#include "Game/Common/BlockManager/BlockManager.h"

class WorldMouse;
class EditorCollision
{
public:

	// 座標を取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }

	// コンストラクタ
	EditorCollision();
	// デストラクタ
	~EditorCollision();
	// 更新
	void Update(IGameObject* object, ID setting);

private:

	// 当たり判定の半径
	static const float HIT_RADIUS;

private:

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_projection;

};

#endif // EDITORCOLLISION