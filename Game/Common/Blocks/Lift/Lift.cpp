/*
 *	@File	Lift.cpp
 *	@Brief	前後移動ブロック。
 *	@Date	2024-02-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Lift.h"

// コンストラクタ
Lift::Lift(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Moving.cmo", L"Resources/Models", position),
	m_offset()			// オフセット
{
	CreateModel();
	SetID(ID::Obj_Lift);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

// デストラクタ
Lift::~Lift()
{
	ReleaseModel();
}

// 更新
void Lift::Update()
{
	// 前後一マスを移動
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds()) * 2;

	m_offset += sinf(timer) * 0.01f;

	// 前後移動
	SetPosition(GetInitialPosition() + SimpleMath::Vector3(0.0f, 0.0f, m_offset));

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Lift::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}