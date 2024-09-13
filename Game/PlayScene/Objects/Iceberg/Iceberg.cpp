/*
 *  @File   Iceberg.cpp
 *  @Brief  氷山。
 *  @Date   2024-02-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Iceberg.h"

// コンストラクタ
Iceberg::Iceberg(SimpleMath::Vector3 position, float rate, float speed)
	:
	BaseObject(L"Resources/Models/Iceberg.cmo", L"Resources/Models"),
	m_rotation(0.0f)			// 回転量
{
	CreateModel();
	SetID(ID::P_Iceberg);
	SetPosition(position);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * rate);
	SetInitialScale(GetScale());

	// 回転速度
	m_speed = speed;
}

// デストラクタ
Iceberg::~Iceberg()
{
	ReleaseModel();
}

// 更新
void Iceberg::Update()
{
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());

	// 回転させる
	m_rotation += timer * m_speed;
	SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(m_rotation), 0.0f));

	// マトリクスを計算
	CreateWorldMatrix();
}

// 描画
void Iceberg::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix(), view, proj, wireframe, option);
}
