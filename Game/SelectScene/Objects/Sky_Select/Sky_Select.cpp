/*
 *	@File	Sky_Select.cpp
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Select.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Sky_Select::ROTATE_SPEED = 0.5f;

//==============================================================================
// コンストラクタ
//==============================================================================
Sky_Select::Sky_Select()
	: IGameObject(L"Resources/Models/ShineSky.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Sky);
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());

	// 自己発光
	GetModel()->UpdateEffects([](IEffect* effect)
		{
			auto _lights = dynamic_cast<IEffectLights*>(effect);
			if (_lights)
			{
				_lights->SetAmbientLightColor(Colors::White);
			}
		}
	);
}

//==============================================================================
// デストラクタ
//==============================================================================
Sky_Select::~Sky_Select()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Sky_Select::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 回転
	SetRotate(SimpleMath::Vector3(0.0f, _timer * ROTATE_SPEED, 0.0f));

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Sky_Select::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}