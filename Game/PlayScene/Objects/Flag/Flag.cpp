/*
 *	@File	Flag.cpp
 *	@Brief	旗オブジェクト
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Flag.h"

 //==============================================================================
 // 定数の設定
 //==============================================================================

//==============================================================================
// コンストラクタ
//==============================================================================
Flag::Flag(const SimpleMath::Vector3& start, const SimpleMath::Vector3& dropped)
	: IGameObject(L"Resources/Models/Flag.cmo", L"Resources/Models")
	, m_droppedPosition{}		// 落下位置
{
	CreateModel();
	SetID(ID::Obj_Flag);
	SetWeight(NON_WEIGHT);

	SetPosition(start);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());

	// 落下先を設定
	m_droppedPosition = dropped;
}

//==============================================================================
// デストラクタ
//==============================================================================
Flag::~Flag()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Flag::Update()
{
	// 落下していく
	SetPosition(UserUtility::Lerp(GetPosition(), m_droppedPosition, 0.1f));

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Flag::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}