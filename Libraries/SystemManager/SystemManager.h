/*
 *	@File	SystemManager.h
 *	@Brief	ゲームを作成するためのシステムの管理クラス。
 *	@Date	2023-06-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SYSTEMMANAGER
#define SYSTEMMANAGER

#include "../SystemDatas/GridFloor/GridFloor.h"
#include "../SystemDatas/RayCast/RayCast.h"
#include "../SystemDatas/DrawSprite/DrawSprite.h"

class SystemManager
{
public:

	// コモンステートの取得
	DirectX::CommonStates* GetCommonStates();
	// ドロースプライトの取得
	DrawSprite* GetDrawSprite();
	// レイキャストの取得
	RayCast* GetRayCast();
	// グリッドフロアの取得
	Debug::GridFloor* GetGridFloor();


	// コンストラクタ
	SystemManager();
	// デストラクタ
	~SystemManager();

private:

	// コモンステート
	DirectX::CommonStates* m_states;
	// ドロースプライト
	DrawSprite* m_sprite;
	// グリッド床
	Debug::GridFloor* m_gridFloor;
	// レイキャスト
	RayCast* m_raycast;
};

#endif // SYSTEMMANAGER