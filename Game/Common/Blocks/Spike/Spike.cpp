/*
 *	@File	Spike.cpp
 *	@Brief	棘オブジェクト(敵)。
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Spike.h"

// 定数の設定
const float Spike::EATING_SPEED = XMConvertToRadians(15.0f);	// 捕食時の回転速度

// コンストラクタ
Spike::Spike(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Spike.cmo", L"Resources/Models", position),
	is_hit(false)				                            // 衝突フラグ
{
	CreateModel();
	SetID(ID::Obj_Spike);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

// デストラクタ
Spike::~Spike()
{
	ReleaseModel();
}

// 更新
void Spike::Update()
{
	// 非アクティブは処理しない
	if (not IsActive()) return;

	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	float sin = (sinf(timer) + 1) * 0.5f + 1;

	// 衝突通知が来たら実行
	if (is_hit)
	{
		// 初期の二倍にする
		SetScale(UserUtility::Lerp(GetScale(), GetInitialScale() * 2, 0.05f));

		// 超速で回転する（捕食）
		SetRotate(GetRotate() + SimpleMath::Vector3::UnitY * EATING_SPEED * sin);
	}
	else
	{
		// 衝突していない間はうごめく
		SetScale(GetInitialScale() * sin * 0.5f);
	}

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Spike::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	// 非アクティブは処理しない
	if (not IsActive()) return;

	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}