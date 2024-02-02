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

	// 境界球半径
	static const float RADIUS;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	StageCollision();
	~StageCollision();

	/// <summary>
	/// 当たり判定の更新
	/// </summary>
	/// <param name="player">プレイヤーポインタ</param>
	/// <param name="blocks">ブロックマネージャポインタ</param>
	/// <returns>なし</returns>
	void Update(Player* player, BlockManager* blocks);

private:

	/// <summary>
	/// 当たり判定処理
	/// </summary>
	/// <param name="playerPos">プレイヤー座標</param>
	/// <param name="blockPos">ブロック座標</param>
	/// <param name="playerScale">プレイヤースケール</param>
	/// <param name="blockScale">ブロックスケール</param>
	/// <param name="push">押し戻しを行うフラグ（trueで押し戻す）</param>
	/// <returns>衝突面</returns>
	Side IsCollision(DirectX::SimpleMath::Vector3* playerPos, const DirectX::SimpleMath::Vector3& blockPos,
		const DirectX::SimpleMath::Vector3& playerScale, const DirectX::SimpleMath::Vector3& blockScale, bool push = false);
};

#endif // STAGECOLLISION