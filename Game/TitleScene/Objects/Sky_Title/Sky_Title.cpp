/*
 *	@File	Sky_Title.cpp
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2023-12-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Title.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Sky_Title::ROTATE_SPEED = 3.0f;

//==============================================================================
// コンストラクタ
//==============================================================================
Sky_Title::Sky_Title()
	: IGameObject(L"Resources/Models/Sky.cmo", L"Resources/Models")
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
Sky_Title::~Sky_Title()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Sky_Title::Update()
{
	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Sky_Title::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}