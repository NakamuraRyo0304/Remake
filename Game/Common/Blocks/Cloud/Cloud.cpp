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
const float Cloud::ROTATE_SPEED = 15.0f;        // 回転速度
const float Cloud::FALL_LIMIT = 180.0f;			// 落下リミット

//==============================================================================
// コンストラクタ
//==============================================================================
Cloud::Cloud(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models", position)
	, is_hit{ false }			// 衝突フラグ
	, is_arrive{ false }		// 到着フラグ
    , m_arrivePosition{}    	// 到着座標
    , m_fallTimer{}				// 落下タイマー
{
	CreateModel();
	SetID(ID::Obj_Cloud);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
    SetInitialScale(GetScale());

	// 到着座標
	m_arrivePosition = GetInitialPosition() + SimpleMath::Vector3::UnitY;

	// 落下時間
	m_fallTimer = 0.0f;
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
		m_fallTimer++;
    }

	// 落下タイマーがリミットを越えたら元に戻す
	if (m_fallTimer > FALL_LIMIT)
	{
		SetPosition(GetInitialPosition());

		// 元の位置に戻ったらタイマーをリセットする
		if (GetPosition() == GetInitialPosition())
		{
			m_fallTimer = 0.0f;
			is_hit = false;
		}
	}

    // マトリクスを作成
    CreateWorldMatrix();
}


//==============================================================================
// 描画処理
//==============================================================================
void Cloud::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}