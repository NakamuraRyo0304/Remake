/*
 *	@File	Head.cpp
 *	@Brief	プレイヤー頭。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Head.h"

//==============================================================================
// 定数の設定
//==============================================================================

//==============================================================================
// コンストラクタ
//==============================================================================
Head::Head()
	: IGameObject(L"Resources/Models/Head.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());
}

//==============================================================================
// デストラクタ
//==============================================================================
Head::~Head()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Head::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Head::Draw(ID3D11DeviceContext1* context, CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(0.5f);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}