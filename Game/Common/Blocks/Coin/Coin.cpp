/*
 *	@File	Coin.cpp
 *	@Brief	コインブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Coin.h"

// 定数の設定
const float Coin::ROTATE_SPEED = 30.0f;

// コンストラクタ
Coin::Coin(SimpleMath::Vector3 position)
	:
	BaseObject(L"Resources/Models/Coin.cmo", L"Resources/Models", position),
	is_hit(false)		// 衝突フラグ
{
	CreateModel();
	SetID(ID::PE_Coin);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

// デストラクタ
Coin::~Coin()
{
	ReleaseModel();
}

// 更新
void Coin::Update()
{
	// 非アクティブは処理しない
	if (not IsActive()) return;

	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// 衝突したら獲得演出
	if (is_hit)
	{
		// 回転しながら小さくなりながら上に上がる（最終的に消える）
		SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition() + SimpleMath::Vector3::UnitY * 0.5f));
		SetScale(UserUtility::Lerp(GetScale(), SimpleMath::Vector3::Zero, 0.05f));
		SetRotate(UserUtility::Lerp(GetRotate(),
			SimpleMath::Vector3::UnitY * XMConvertToRadians(timer * ROTATE_SPEED * 2)));

		// スケールが0になったら描画を切る
		if (GetScale().LengthSquared() < 0.01f)
		{
			SetActive(false);
		}
	}
	else
	{
		SetRotate(UserUtility::Lerp(GetRotate(),
			SimpleMath::Vector3::UnitY * XMConvertToRadians(timer * ROTATE_SPEED)));
	}

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void Coin::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	// 非アクティブは処理しない
	if (not IsActive()) return;

	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}