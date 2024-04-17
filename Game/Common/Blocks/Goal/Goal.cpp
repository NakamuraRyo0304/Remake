/*
 *  @File   Goal.cpp
 *  @Brief  ゴールオブジェクト。
 *  @Date   2024-02-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Goal.h"

// コンストラクタ
Goal::Goal(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Goal.cmo", L"Resources/Models", position),
	is_hit(false)	// 衝突フラグ
{
	CreateModel();
	SetID(ID::Obj_Goal);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());

	// 衝突フラグをオフにする
	is_hit = false;
}

// デストラクタ
Goal::~Goal()
{
	ReleaseModel();
}

// 更新
void Goal::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Goal::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}