/*
 *	@File	Logo.cpp
 *	@Brief	タイトルロゴオブジェクト。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Logo.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector3  Logo::MOVE_POS = { 0.0f,2.0f,0.0f };	// 移動先座標
const float Logo::MODEL_SCALE = 1.5f;							// モデルのスケール

//==============================================================================
// コンストラクタ
//==============================================================================
Logo::Logo()
	: IGameObject(L"Resources/Models/TitleLogoVer2.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Logo);
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3(0.0f,30.0f,50.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * MODEL_SCALE);
	SetInitialScale(GetScale());
}

//==============================================================================
// デストラクタ
//==============================================================================
Logo::~Logo()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Logo::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	float _01Sin = sinf(_timer + 1) * 0.5f;

	// 回転
	SetRotate(SimpleMath::Vector3::UnitX * _01Sin);

	// 移動
	SetPosition(UserUtility::Lerp(
		GetPosition(), MOVE_POS, 0.1f));

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Logo::Draw(ID3D11DeviceContext1* context, CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}