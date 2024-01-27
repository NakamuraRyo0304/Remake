/*
 *	@File	Cloud.cpp
 *	@Brief	雲ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Cloud.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Cloud::ROTATE_SPEED = 15.0f;

//==============================================================================
// コンストラクタ
//==============================================================================
Cloud::Cloud(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models")
	, is_hit{ false }			// 衝突フラグ
	, is_arrive{ false }		// 到着フラグ
    , m_arrivePosition{}    	// 到着座標
{
	CreateModel();
	SetID(ID::Default);
	SetName(L"Cloud");
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);

	// 到着座標
	m_arrivePosition = GetInitialPosition() + SimpleMath::Vector3::UnitY;
}

//==============================================================================
// デストラクタ
//==============================================================================
Cloud::~Cloud()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Cloud::Update()
{
    float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

    // 回転行列
    SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(timer * ROTATE_SPEED), 0.0f));

    if (is_hit)
    {
        // 上昇させる
        SetPosition(UserUtility::Lerp(GetPosition(), m_arrivePosition, 0.1f));

        // 到達したらフラグをOFF
        if (std::abs(GetPosition().y - m_arrivePosition.y) < 0.01f)
        {
            is_arrive = true;
        }
    }
    else
    {
        // 降下させる
        SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition(), 0.1f));

        // 元の位置に戻ったらフラグをOFF
        if (std::abs(GetPosition().y - GetInitialPosition().y) < 0.01f)
        {
            is_arrive = false;
        }
    }

    // マトリクスを作成
    CreateWorldMatrix();
}


//==============================================================================
// 描画処理
//==============================================================================
void Cloud::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}