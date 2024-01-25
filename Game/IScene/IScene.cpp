/*
 *	@File	IScene.cpp
 *	@Brief	基底クラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "IScene.h"

//==============================================================================
// コンストラクタ
//==============================================================================
IScene::IScene()
	: m_system{std::make_shared<SystemManager>()}	// システムマネージャ
	, m_nextScene{SCENE::NONE}						// 次のシーン
	, m_windowSize{}								// 画面のサイズ
	, m_fadeSpeed{4.0f}								// フェードの速度
	, m_fadeValue{0.0f}								// フェードの現在値
	, is_changeFlag{false}							// シーン切り替えフラグ
	, is_fadeEnd{false}								// フェード終了フラグ
{
	// 作成されていなければシステムを作成
	if (not m_system)
	{
		m_system = std::make_shared<SystemManager>();
	}
}