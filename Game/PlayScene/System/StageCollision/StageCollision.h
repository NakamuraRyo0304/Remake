/*
 *	@File	StageCollision.h
 *	@Brief	ステージの当たり判定。
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef STAGECOLLISION
#define STAGECOLLISION

// ゲームオブジェクト
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/Objects/Player/Player.h"

class StageCollision
{
public:

	// コンストラクタ
	StageCollision();
	// デストラクタ
	~StageCollision();
	// 初期化
	void Initialize(BlockManager* blocks);
	// 更新
	void Update(Player* player);

private:

	// 衝突面
	enum Side
	{
		None, Left, Right, Up, Down, Front, Behind
	};

	// 境界球半径
	static const float RADIUS;
	// 分割数
	static const int NUM_DIVISIONS = 8;

private:

	// 固有処理
	void PerformEngenProc(Player* player, BaseObject* block, DirectX::SimpleMath::Vector3 newPos, Side side);

	// 当たり判定処理
	Side IsCube(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale);

private:

	// 判定オブジェクト配列
	std::vector<BaseObject*> m_objects;

};

#endif // STAGECOLLISION