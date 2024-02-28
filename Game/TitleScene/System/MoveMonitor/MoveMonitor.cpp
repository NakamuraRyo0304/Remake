/*
 *  @File   MoveMonitor.cpp
 *  @Brief  画面監視者。
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MoveMonitor.h"

//==============================================================================
// コンストラクタ
//==============================================================================
MoveMonitor::MoveMonitor()
	: is_moveMouse{ false }		// 動作通知フラグ（動いたらTrue）
	, m_length{}			    // 最終長さ
{
}

//==============================================================================
// デストラクタ
//==============================================================================
MoveMonitor::~MoveMonitor()
{
}

//==============================================================================
// 更新関数
//==============================================================================
void MoveMonitor::Update()
{
    auto _ms = Mouse::Get().GetState();
    auto _msp = SimpleMath::Vector2(static_cast<float>(_ms.x), static_cast<float>(_ms.y));

    // 現在のマウス座標と0:0の距離を計算
    float _length = SimpleMath::Vector2::Distance(SimpleMath::Vector2::Zero, _msp);

    // 一定以上の距離が動いた場合に通知フラグを立てる
    if (_length != m_length)
    {
        is_moveMouse = true;
    }
    else
    {
        is_moveMouse = false;
    }

    // 座標からの距離を更新
    m_length = _length;
}
