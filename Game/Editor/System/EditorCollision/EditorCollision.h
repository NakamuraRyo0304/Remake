/*
 *	@File	EditorCollision.h
 *	@Brief	エディタの当たり判定。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORCOLLISION
#define EDITORCOLLISION

//==============================================================================
// ブロックマネージャ
//==============================================================================
#include "Game/Common/BlockManager/BlockManager.h"

class WorldMouse;
class EditorCollision
{
private:

	// 座標
	DirectX::SimpleMath::Vector3 m_position;

	// ビュー行列・射影行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

private:

	// 当たり判定の半径
	static const float HIT_RADIUS;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	EditorCollision();
	~EditorCollision();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="object">オブジェクトポインタ</param>
	/// <param name="setting">選択しているブロックのID</param>
	/// <returns>なし</returns>
	void Update(IGameObject* object, ID setting);

public:

	// 座標を取得
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
};

#endif // EDITORCOLLISION