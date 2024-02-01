/*
 *	@File	WorldMouse.cpp
 *	@Brief	ワールド変換したマウス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/RayCast/RayCast.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "WorldMouse.h"

//==============================================================================
// コンストラクタ
//==============================================================================
WorldMouse::WorldMouse(SimpleMath::Matrix view, SimpleMath::Matrix proj)
    : m_view{ view }            // ビュー行列
    , m_projection{ proj }      // 射影行列
    , m_position{}              // 座標
    , m_height{}                // Y座標の高さ
{
    m_ray = std::make_unique<RayCast>();
}

//==============================================================================
// デストラクタ
//==============================================================================
WorldMouse::~WorldMouse()
{
    m_ray.reset();
}

//==============================================================================
// 更新処理
//==============================================================================
void WorldMouse::Update(const float& moveSpeed)
{
    float _fps = static_cast<float>(DX::StepTimer::GetInstance().GetFramesPerSecond());

    // レイの更新
    m_ray->Update();

    // キーボード・マウスの取得
    auto _key = Keyboard::Get().GetState();
    auto _mouse = Mouse::Get().GetState();

    // 右クリック＋左シフトで降下する
    if (_mouse.rightButton && _key.LeftShift)
    {
        m_height -= moveSpeed * _fps;
    }
    // 右クリックで上昇
    else if (_mouse.rightButton)
    {
        m_height += moveSpeed * _fps;
    }

    // クランプ処理
    m_height = UserUtility::Clamp(m_height, 0.0f, 5.0f);

    // 座標を設定
    m_position =
        m_ray->GetConvertedPosition() + SimpleMath::Vector3(0.0f, m_height, 0.0f);
}

//==============================================================================
// 描画処理
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}