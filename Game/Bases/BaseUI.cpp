/*
 *  @File   FileName.h
 *  @Brief  処理内容。
 *  @Date   2024-00-00
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "BaseUI.h"

// コンストラクタ
BaseUI::BaseUI(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	m_screenSize(scS),			// 画面サイズ
	m_maxScreenSize(mscs),		// 最大画面サイズ
	m_screenRate(scS / mscs)	// 画面比率
{
}

// デストラクタ
BaseUI::~BaseUI()
{
}
