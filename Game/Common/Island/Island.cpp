/*
 *  @File   Island.cpp
 *  @Brief  �Ǔ��B
 *  @Date   2024-02-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Island.h"

// �R���X�g���N�^
Island::Island(SimpleMath::Vector3 position, float rate, float speed)
	:
	IGameObject(L"Resources/Models/Island.cmo", L"Resources/Models"),
	m_rotation(0.0f)			// ��]��
{
	CreateModel();
	SetID(ID::Back_Island);
	SetWeight(NON_WEIGHT);
	SetPosition(position);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * rate);
	SetInitialScale(GetScale());

	// ��]���x
	m_speed = speed;
}

// �f�X�g���N�^
Island::~Island()
{
	ReleaseModel();
}

// �X�V
void Island::Update()
{
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());

	// ��]������
	m_rotation += timer * m_speed;
	SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(m_rotation), 0.0f));

	// �}�g���N�X���v�Z
	CreateWorldMatrix();
}

// �`��
void Island::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix(), view, proj, wireframe, option);
}
