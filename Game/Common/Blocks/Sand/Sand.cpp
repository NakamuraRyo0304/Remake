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
Sand::Sand(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Sand.cmo", L"Resources/Models", position)
	, is_hit{ false }
{
	CreateModel();
	SetID(ID::Obj_Sand);
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
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}