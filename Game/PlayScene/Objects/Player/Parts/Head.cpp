/*
 *	@File	Head.cpp
 *	@Brief	プレイヤー頭。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "Head.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Head::SCALE = 0.5f;			// モデルのスケール
const float Head::ROT_POWER = 15.0f;	// 首振りの強さ

//==============================================================================
// コンストラクタ
//==============================================================================
Head::Head()
	: IGameObject(L"Resources/Models/pHead.cmo", L"Resources/Models")
	, m_states{ MoveStates::Idling }		// アイドル状態
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());

	// タイマー作成
	m_timer = std::make_unique<Timer>(Timer::Mode::infinited);
	m_timer->Start();
}

//==============================================================================
// デストラクタ
//==============================================================================
Head::~Head()
{
	ReleaseModel();
	m_timer.reset();
}

//==============================================================================
// 更新処理
//==============================================================================
void Head::Update()
{
	m_timer->Update();

	// アイドル状態はきょろきょろする
	if (m_states == MoveStates::Idling)
	{
		float _value = XMConvertToRadians(sinf(m_timer->GetCount()) * ROT_POWER);
		SetRotate(UserUtility::Lerp(GetRotate(), SimpleMath::Vector3::UnitY * _value));
	}
	else if(m_states == MoveStates::Walking)
	{
		SetRotate(UserUtility::Lerp(GetRotate(), SimpleMath::Vector3::Zero));
	}

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Head::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(SCALE);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}