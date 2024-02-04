/*
 *	@File	EditChara.cpp
 *	@Brief	判定用オブジェクト（エディタ）。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "EditChara.h"

//==============================================================================
// コンストラクタ
//==============================================================================
EditChara::EditChara(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Bird.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
}

//==============================================================================
// デストラクタ
//==============================================================================
EditChara::~EditChara()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void EditChara::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void EditChara::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}