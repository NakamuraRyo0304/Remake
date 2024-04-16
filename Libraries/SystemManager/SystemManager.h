/*
 *	@File	SystemManager.h
 *	@Brief	ゲームを作成するためのシステムの管理クラス。
 *	@Date	2023-06-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SYSTEMMANAGER
#define SYSTEMMANAGER

#include "Game/GameMain.h"

//-------------------------------------------------------------------------------------//
// システムのインクルード
#include "../SystemDatas/GridFloor/GridFloor.h"
#include "../SystemDatas/RayCast/RayCast.h"
#include "../SystemDatas/DrawSprite/DrawSprite.h"
//-------------------------------------------------------------------------------------//

class SystemManager
{
private:
	// コモンステート
	DirectX::CommonStates*			m_states;
	// ドロースプライト
	DrawSprite*						m_sprite;
	// グリッド床
	Debug::GridFloor*               m_gridFloor;
	// レイキャスト
	RayCast*						m_raycast;

public:
	// 共通の作成
	void CreateResources();

	// コモンステートの取得
	DirectX::CommonStates* GetCommonStates();

	// ドロースプライトの取得
	DrawSprite* GetDrawSprite();

	// レイキャストの取得
	RayCast* GetRayCast();

	// グリッドフロアの取得
	Debug::GridFloor* GetGridFloor();

public:
	SystemManager();
	~SystemManager();
};

#endif // SYSTEMMANAGER