/*
 *	@File	Coin.cpp
 *	@Brief	コインブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Coin.h"

//==============================================================================
// 定数の設定
//==============================================================================


//==============================================================================
// コンストラクタ
//==============================================================================
Coin::Coin(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Coin.cmo", L"Resources/Models", position)
	, is_hit{ false }		// 衝突フラグ
	, is_active{ true }		// アクティブフラグ
{
	CreateModel();
	SetID(ID::Obj_Coin);
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
Coin::~Coin()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Coin::Update()
{
	// 非アクティブは処理しない
	if (not is_active) return;

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Coin::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	// 非アクティブは処理しない
	if (not is_active) return;

	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}