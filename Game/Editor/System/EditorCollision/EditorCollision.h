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

	// ワールドマウス
	std::unique_ptr<WorldMouse> m_worldMouse;

	// ビュー行列・射影行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

private:

	// 当たり判定の半径
	static const float HIT_RADIUS;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	EditorCollision(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	~EditorCollision();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="object">オブジェクトポインタ</param>
	/// <param name="setting">選択しているブロックのID</param>
	/// <returns>なし</returns>
	void Update(IGameObject* object, ID setting);

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

public:

	// ワールドマウスの座標
	DirectX::SimpleMath::Vector3 GetWorldMousePosition();
};

#endif // EDITORCOLLISION