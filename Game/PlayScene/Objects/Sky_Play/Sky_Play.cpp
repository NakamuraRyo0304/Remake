/*
 *	@File	Sky_Play.cpp
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Play.h"

// 定数の設定
const float Sky_Play::ROTATE_SPEED = 0.5f;		// 回転速度

// コンストラクタ
Sky_Play::Sky_Play()
	:
	IGameObject(L"Resources/Models/Sky.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Sky);
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

// デストラクタ
Sky_Play::~Sky_Play()
{
	ReleaseModel();
}

// 更新
void Sky_Play::Update()
{
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 回転
	SetRotate(SimpleMath::Vector3(0.0f, timer * ROTATE_SPEED, 0.0f));

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Sky_Play::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}