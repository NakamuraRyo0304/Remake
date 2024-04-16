/*
 *	@File	Cloud.cpp
 *	@Brief	雲ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "Cloud.h"

// 定数の設定
const float Cloud::LIMIT = 3.5f;		// 動作時間

// コンストラクタ
Cloud::Cloud(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models", position),
	is_hit(false)						// 衝突フラグ
{
	CreateModel();
	SetID(ID::Obj_Cloud);
	SetWeight(1.0f);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
    SetInitialScale(GetScale());

	// 落下時間
	m_timer = std::make_unique<Timer>(Timer::Mode::limited, LIMIT);
}

// デストラクタ
Cloud::~Cloud()
{
	ReleaseModel();
}

// 更新
void Cloud::Update()
{
    // 回転行列
    SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(m_timer->GetCount()), 0.0f));

    if (is_hit)
    {
		// 1度だけ更新する
		if (m_timer->GetCount() == 0.0f)
		{
			m_timer->Start();
		}

		// 上下させる
        SetPosition(UserUtility::Lerp(GetPosition(),
			GetInitialPosition() + sinf(m_timer->GetCount()) * SimpleMath::Vector3::UnitY * 1.1f));

		// タイマーを更新する
		m_timer->Update();
    }

	// アラームが鳴ったら戻す
	if (m_timer->Alarm())
	{
		SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition()));
		m_timer->Reset();
		is_hit = false;
	}

    // マトリクスを作成
    CreateWorldMatrix();
}

// 描画
void Cloud::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}