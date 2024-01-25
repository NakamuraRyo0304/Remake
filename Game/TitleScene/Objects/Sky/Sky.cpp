/*
 *	@File	Sky.cpp
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2023-12-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Sky::ROTATE_SPEED = 3.0f;

//==============================================================================
// コンストラクタ
//==============================================================================
Sky::Sky()
	: IGameObject(L"Resources/Models/ShineSky.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Default);
	SetName(L"SkyDome");
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);

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
Sky::~Sky()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Sky::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 回転
	SetRotate(SimpleMath::Vector3(_timer * ROTATE_SPEED, 0.0f, 0.0f));

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Sky::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}