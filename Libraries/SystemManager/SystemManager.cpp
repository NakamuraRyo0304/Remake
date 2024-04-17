/*
 *	@File	SystemManager.cpp
 *	@Brief	ゲームを作成するためのシステムの管理クラス。
 *	@Date	2023-06-02
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "SystemManager.h"

// コンストラクタ
SystemManager::SystemManager()
	:
	m_states(nullptr),
	m_sprite(nullptr),
	m_raycast(nullptr),
	m_gridFloor(nullptr)
{
}

// デストラクタ
SystemManager::~SystemManager()
{
	delete m_states;
	delete m_sprite;
	delete m_raycast;
	delete m_gridFloor;
}

// コモンステート
CommonStates* SystemManager::GetCommonStates()
{
	if (not m_states)
	{
		m_states = new CommonStates(DX::DeviceResources::GetInstance()->GetD3DDevice());
	}
	return m_states;
}

// スプライト
DrawSprite* SystemManager::GetDrawSprite()
{
	if (not m_sprite)
	{
		m_sprite = new DrawSprite();
	}
	return m_sprite;
}

// レイキャスト
RayCast* SystemManager::GetRayCast()
{
	if (not m_raycast)
	{
		m_raycast = new RayCast();
	}
	return m_raycast;
}

// グリッドフロア
Debug::GridFloor* SystemManager::GetGridFloor()
{
	if (not m_gridFloor)
	{
		m_gridFloor = new Debug::GridFloor(50, 50);
	}
	return m_gridFloor;
}
