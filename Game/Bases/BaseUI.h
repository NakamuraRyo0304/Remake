/*
 *  @File   BaseUI.h
 *  @Brief  UIの基底クラス。
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BASEUI
#define BASEUI

// インターフェース
#include "Game/Interfaces/IUserInterface.h"

// 共通機能
#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class BaseUI : public IUserInterface
{
public:

	// 画面拡大率を取得
	const DirectX::SimpleMath::Vector2& GetScreenRate() { return m_screenRate; }
	// 画面サイズを取得
	const DirectX::SimpleMath::Vector2& GetScreenSize() { return m_screenSize; }
	// 最大画面サイズを取得
	const DirectX::SimpleMath::Vector2& GetMaxScreenSize() { return m_maxScreenSize; }


	// コンストラクタ
	BaseUI(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~BaseUI();

private:

	// 画面サイズ
	DirectX::SimpleMath::Vector2 m_screenSize;
	// 最大画面サイズ
	DirectX::SimpleMath::Vector2 m_maxScreenSize;
	// 画面拡大率
	DirectX::SimpleMath::Vector2 m_screenRate;

};

#endif // BASEUI