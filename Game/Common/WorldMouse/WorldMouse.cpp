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
// 定数の設定
//==============================================================================
const float WorldMouse::MAX_HEIGHT = 5.0f;          // 最高高度
const float WorldMouse::PLAY_HEIGHT = 1.0f;         // プレイ時の高度

//==============================================================================
// エイリアス宣言
//==============================================================================
using MOUSE_BUTTON = Mouse::ButtonStateTracker;

//==============================================================================
// コンストラクタ
//==============================================================================
WorldMouse::WorldMouse()
    : m_position{}              // 座標
    , m_height{}                // Y座標の高さ
    , is_playing{ false }       // デフォルトはエディタモード
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
void WorldMouse::Update()
{
    // レイの更新
    m_ray->Update();

    // プレイモードは最高高度にする
    if (is_playing)
    {
        // 座標を設定
        m_position = m_ray->GetConvertedPosition();
        m_position.y = PLAY_HEIGHT;
    }
    else
    {
        // キーボード・マウスの取得
        auto _key = Keyboard::Get().GetState();
        auto& _mt = Input::GetInstance()->GetMouseTrack();

        // 右クリック＋左シフトで降下する
        if (_mt->rightButton == MOUSE_BUTTON::PRESSED && _key.LeftShift)
        {
            m_height--;
        }
        // 右クリックで上昇
        else if (_mt->rightButton == MOUSE_BUTTON::PRESSED)
        {
            m_height++;
        }

        // クランプ処理
        m_height = UserUtility::Clamp(m_height, 0, 5);

        // 座標を設定(線形補間移動)
        m_position = m_ray->GetConvertedPosition();
        m_position.y = static_cast<float>(m_height);
    }
}

//==============================================================================
// 描画処理
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}