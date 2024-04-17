/*
 *	@File	Flag.cpp
 *	@Brief	旗オブジェクト
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Flag.h"

// 定数の設定
const float Flag::FALL_SPEED = 0.05f;		// 落下速度
const float Flag::CLOSED_MATCH = 0.1f;		// 近似一致

// コンストラクタ
Flag::Flag(const SimpleMath::Vector3& start, const SimpleMath::Vector3& dropped)
	:
	IGameObject(L"Resources/Models/Flag.cmo", L"Resources/Models"),
	m_droppedPosition(),		            // 落下位置
	is_arrive(false)			            // 到着フラグ
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

// デストラクタ
Flag::~Flag()
{
	ReleaseModel();
}

// 更新
void Flag::Update()
{
	// 落下していく
	SetPosition(UserUtility::Lerp(GetPosition(), m_droppedPosition, FALL_SPEED));

	// 位置が決定したらTrue
	if (std::abs(GetPosition().y - m_droppedPosition.y) < CLOSED_MATCH)
	{
		is_arrive = true;
	}

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Flag::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}