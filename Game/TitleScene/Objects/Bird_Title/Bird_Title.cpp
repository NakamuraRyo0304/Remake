/*
 *	@File	Bird_Title.cpp
 *	@Brief	タイトルに表示するトリ。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Bird_Title.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float Bird_Title::RESTART_LINE = -10.0f;
const float Bird_Title::BIRD_SCALE = 2.0f;

//==============================================================================
// コンストラクタ
//==============================================================================
Bird_Title::Bird_Title()
	: IGameObject(L"Resources/Models/Bird.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Bird);
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3(0.0f, 30.0f, -5.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * BIRD_SCALE);
	SetInitialScale(GetScale());

	// Xをランダムに変更
	RandomXPosition();
}

//==============================================================================
// デストラクタ
//==============================================================================
Bird_Title::~Bird_Title()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void Bird_Title::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 落下
	SetPosition(GetPosition() - SimpleMath::Vector3::UnitY * 0.1f);

	// ラインより下に行ったら再スタート
	if (GetPosition().y < RESTART_LINE)
	{
		RandomXPosition();
	}

	// 回転
	SetRotate(SimpleMath::Vector3::UnitX * _timer +
		SimpleMath::Vector3::UnitY * _timer + SimpleMath::Vector3::UnitZ * sinf(_timer));

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void Bird_Title::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}

//==============================================================================
// ランダムでX座標を再抽選する
//==============================================================================
void Bird_Title::RandomXPosition()
{
	// ランダムな座標を指定
	float _x = static_cast<float>(UserUtility::Random(-10.0, 10.0));

	// 座標をセットする
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitX * _x);
}
