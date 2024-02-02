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
void EditChara::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}