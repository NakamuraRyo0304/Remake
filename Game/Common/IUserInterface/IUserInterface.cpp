/*
 *	@File	IUserInterface.cpp
 *	@Brief	UIクラス。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "IUserInterface.h"

//==============================================================================
// コンストラクタ
//==============================================================================
IUserInterface::IUserInterface(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: m_maxScreenSize{ mscs }		// 最大サイズ
	, m_screenSize{ scS }			// 画面サイズ
	, m_screenRate{ scS / mscs }	// 画面拡大率
{
}
