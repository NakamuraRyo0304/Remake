/*
 *	@File	WorldMouse.cpp
 *	@Brief	ワールド変換したマウス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/RayCast/RayCast.h"
#include "WorldMouse.h"

//==============================================================================
// コンストラクタ
//==============================================================================
WorldMouse::WorldMouse(SimpleMath::Matrix view, SimpleMath::Matrix proj)
    : m_view{ view }            // ビュー行列
    , m_projection{ proj }      // 射影行列
    , m_position{}              // 座標
{
    m_ray = std::make_unique<RayCast>();
}

//==============================================================================
// デストラクタ
//==============================================================================
WorldMouse::~WorldMouse()
{
}

//==============================================================================
// 更新処理
//==============================================================================
void WorldMouse::Update()
{
    // 例の更新
    m_ray->Update();

    // 座標を取得
    m_position = m_ray->GetConvertedPosition();
}

//==============================================================================
// 描画処理
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}