/*
 *	@File	Sky_Select.cpp
 *	@Brief	�X�J�C�h�[���I�u�W�F�N�g�B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Select.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Sky_Select::ROTATE_SPEED = 0.5f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Sky_Select::Sky_Select()
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

	// ���Ȕ���
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
// �f�X�g���N�^
//==============================================================================
Sky_Select::~Sky_Select()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Sky_Select::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ��]
	SetRotate(SimpleMath::Vector3(0.0f, _timer * ROTATE_SPEED, 0.0f));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Sky_Select::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}