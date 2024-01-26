/*
 *	@File	Sand.cpp
 *	@Brief	砂ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Sand.h"

//==============================================================================
// 定数の設定
//==============================================================================


//==============================================================================
// コンストラクタ
//==============================================================================
Sand::Sand()
	: IGameObject(L"Resources/Models/Sand.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Default);
	SetName(L"Sand");
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(0.0f, 0.0f, 0.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
}

//==============================================================================
// デストラクタ
//==============================================================================
Sand::~Sand()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Sand::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Sand::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}