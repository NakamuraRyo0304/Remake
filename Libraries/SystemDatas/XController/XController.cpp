/*
 *	@File	XController.cpp
 *	@Brief	Xboxコントローラー。
 *	@Date	2023-12-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "XController.h"

//==============================================================================
// コンストラクタ
//==============================================================================
XController::XController()
{
    m_gamePad = std::make_unique<GamePad>();
}

//==============================================================================
// デストラクタ
//==============================================================================
XController::~XController()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void XController::Update()
{
    auto state = m_gamePad->GetState(0);
    m_padTracker.Update(state);
}

//==============================================================================
// パッドトラッカーを取得
//==============================================================================
const GamePad::ButtonStateTracker& XController::GetPadTrack()
{
    return m_padTracker;
}
