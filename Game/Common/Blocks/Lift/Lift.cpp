/*
 *	@File	Lift.cpp
 *	@Brief	�O��ړ��u���b�N�B
 *	@Date	2024-02-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Lift.h"

// �R���X�g���N�^
Lift::Lift(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Moving.cmo", L"Resources/Models", position),
	m_offset()			// �I�t�Z�b�g
{
	CreateModel();
	SetID(ID::Obj_Lift);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

// �f�X�g���N�^
Lift::~Lift()
{
	ReleaseModel();
}

// �X�V
void Lift::Update()
{
	// �O���}�X���ړ�
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds()) * 2;

	m_offset += sinf(timer) * 0.01f;

	// �O��ړ�
	SetPosition(GetInitialPosition() + SimpleMath::Vector3(0.0f, 0.0f, m_offset));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void Lift::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}