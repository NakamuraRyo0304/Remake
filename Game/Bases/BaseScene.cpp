/*
 *  @File   BaseScene.cpp
 *  @Brief  シーンの基底クラス。
 *  @Date   2024-04-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "BaseScene.h"

// コンストラクタ
BaseScene::BaseScene()
	:
	m_system{ std::make_shared<SystemManager>() },	// システムマネージャ
	m_nextScene(SCENE::NONE),						// 次のシーン
	m_windowSize(FULL_HD),							// 画面のサイズ
	m_fadeSpeed(4.0f),								// フェードの速度
	m_fadeValue(0.0f),								// フェードの現在値
	is_changeFlag(false),							// シーン切り替えフラグ
	is_fadeEnd(false)								// フェード終了フラグ
{
}

// デストラクタ
BaseScene::~BaseScene()
{
	m_system.reset();
}
