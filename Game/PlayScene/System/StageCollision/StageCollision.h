/*
 *	@File	StageCollision.h
 *	@Brief	ステージの当たり判定。
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef STAGECOLLISION
#define STAGECOLLISION

//==============================================================================
// ゲームオブジェクト
//==============================================================================
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/Objects/Player/Player.h"

class StageCollision
{
private:

	// 衝突面
	enum Side
	{
		None, Left, Right, Up, Down, Front, Behind
	};

	// 判定オブジェクト配列
	std::vector<IGameObject*> m_objects;

	// 境界球半径
	static const float RADIUS;

	// 分割数
	static const int NUM_DIVISIONS = 8;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	StageCollision();
	~StageCollision();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="blocks">ブロックマネージャポインタ</param>
	/// <returns>なし</returns>
	void Initialize(BlockManager* blocks);

	/// <summary>
	/// 当たり判定の更新
	/// </summary>
	/// <param name="player">プレイヤーポインタ</param>
	/// <returns>なし</returns>
	void Update(Player* player);

private:

	/// <summary>
	/// 固有処理
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="block">ブロック</param>
	/// <param name="newPos">変更後の座標</param>
	/// <param name="side">当たった面</param>
	/// <returns>なし</returns>
	void PerformEngenProc(Player* player, IGameObject* block, DirectX::SimpleMath::Vector3 newPos, Side side);

	/// <summary>
	/// 当たり判定処理
	/// </summary>
	/// <param name="playerPos">プレイヤー座標</param>
	/// <param name="blockPos">ブロック座標</param>
	/// <param name="playerScale">プレイヤースケール</param>
	/// <param name="blockScale">ブロックスケール</param>
	/// <returns>衝突面</returns>
	Side IsCube(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale);
};

#endif // STAGECOLLISION