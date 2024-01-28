/*
 *	@File	Air.cpp
 *	@Brief	判定用オブジェクト（エディタ）。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Air.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Air::Air(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Sand.cmo", L"Resources/Models")
	, is_hit{ false }		// 衝突フラグ
	, is_active{ true }		// アクティブフラグ
{
	CreateModel();
	SetID(ID::Obj_Air);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
}

//==============================================================================
// デストラクタ
//==============================================================================
Air::~Air()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Air::Update()
{
	// 非アクティブは処理しない
	if (not is_active) return;

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Air::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	UNREFERENCED_PARAMETER(states);
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
	UNREFERENCED_PARAMETER(no_use_here);
}