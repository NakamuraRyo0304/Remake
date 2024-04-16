/*
 *	@File	Flozen.cpp
 *	@Brief	氷ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Flozen.h"

// コンストラクタ
Flozen::Flozen(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Flozen.cmo", L"Resources/Models", position)
{
	CreateModel();
	SetID(ID::Obj_Flozen);
	SetWeight(1.0f);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

//==============================================================================
// デストラクタ
//==============================================================================
Flozen::~Flozen()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Flozen::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Flozen::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}