/*
 *	@File	Sky_Title.cpp
 *	@Brief	�X�J�C�h�[���I�u�W�F�N�g�B
 *	@Date	2023-12-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Title.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Sky_Title::ROTATE_SPEED = 3.0f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Sky_Title::Sky_Title()
	: IGameObject(L"Resources/Models/ShineSky.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Sky);
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());

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
Sky_Title::~Sky_Title()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Sky_Title::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ��]
	SetRotate(SimpleMath::Vector3(_timer * ROTATE_SPEED, _timer * 0.5f, 0.0f));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Sky_Title::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}