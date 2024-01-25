/*
 *	@File	Logo.cpp
 *	@Brief	�^�C�g�����S�I�u�W�F�N�g�B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Logo.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector3  Logo::MOVE_POS = { 0.0f,0.0f,0.0f };
const float Logo::MODEL_SCALE = 1.5f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Logo::Logo()
	: IGameObject(L"Resources/Models/TitleLogoVer2.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Default);
	SetName(L"Logo");
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3(0.0f,30.0f,50.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * MODEL_SCALE);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Logo::~Logo()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Logo::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	float _01Sin = sinf(_timer + 1) * 0.5f;

	// ��]
	SetRotate(SimpleMath::Vector3::UnitX * _01Sin);

	// �ړ�
	SetPosition(UserUtility::Lerp(
		GetPosition(), MOVE_POS, 0.1f));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Logo::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}