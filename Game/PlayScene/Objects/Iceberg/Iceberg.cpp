/*
 *  @File   Iceberg.cpp
 *  @Brief  �X�R�B
 *  @Date   2024-02-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Iceberg.h"

// �R���X�g���N�^
Iceberg::Iceberg(SimpleMath::Vector3 position, float rate, float speed)
	:
	BaseObject(L"Resources/Models/Iceberg.cmo", L"Resources/Models"),
	m_rotation(0.0f)			// ��]��
{
	CreateModel();
	SetID(ID::P_Iceberg);
	SetPosition(position);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * rate);
	SetInitialScale(GetScale());

	// ��]���x
	m_speed = speed;
}

// �f�X�g���N�^
Iceberg::~Iceberg()
{
	ReleaseModel();
}

// �X�V
void Iceberg::Update()
{
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());

	// ��]������
	m_rotation += timer * m_speed;
	SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(m_rotation), 0.0f));

	// �}�g���N�X���v�Z
	CreateWorldMatrix();
}

// �`��
void Iceberg::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix(), view, proj, wireframe, option);
}
