/*
 *  @File   MoveMonitor.cpp
 *  @Brief  画面監視者。
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MoveMonitor.h"

// コンストラクタ
MoveMonitor::MoveMonitor()
	:
	m_length(),			// 最終長さ
    is_moveMouse(false) // 動作通知フラグ（動いたらTrue）
{
}

// デストラクタ
MoveMonitor::~MoveMonitor()
{
}

// 更新
void MoveMonitor::Update()
{
    auto ms = Mouse::Get().GetState();
    auto msPosition = SimpleMath::Vector2(static_cast<float>(ms.x), static_cast<float>(ms.y));

    // 現在のマウス座標と0:0の距離を計算
    float length = SimpleMath::Vector2::Distance(SimpleMath::Vector2::Zero, msPosition);

    // 一定以上の距離が動いた場合に通知フラグを立てる
    if (length != m_length)
    {
        is_moveMouse = true;
    }
    else
    {
        is_moveMouse = false;
    }

    // 座標からの距離を更新
    m_length = length;
}
