/*
 *	@File	Bird_Title.cpp
 *	@Brief	�^�C�g���ɕ\������g���B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Bird_Title.h"

// �萔�̐ݒ�
const float Bird_Title::BIRD_SCALE = 2.0f; // �X�P�[��

// �R���X�g���N�^
Bird_Title::Bird_Title()
	:
	BaseObject(L"Resources/Models/pAll.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Bird);
	SetPosition(SimpleMath::Vector3(5.0f, 0.0f, 10.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * BIRD_SCALE);
	SetInitialScale(GetScale());
}

// �f�X�g���N�^
Bird_Title::~Bird_Title()
{
	ReleaseModel();
}

// �X�V
void Bird_Title::Update()
{
	// ��]
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	SetRotate(SimpleMath::Vector3::UnitY * (XMConvertToRadians(90.0f) + sinf(timer) * 0.5f));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void Bird_Title::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}