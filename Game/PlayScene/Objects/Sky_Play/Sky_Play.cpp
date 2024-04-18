/*
 *	@File	Sky_Play.cpp
 *	@Brief	�X�J�C�h�[���I�u�W�F�N�g�B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Sky_Play.h"

// �萔�̐ݒ�
const float Sky_Play::ROTATE_SPEED = 0.5f;		// ��]���x

// �R���X�g���N�^
Sky_Play::Sky_Play()
	:
	IGameObject(L"Resources/Models/Sky.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Sky);
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

// �f�X�g���N�^
Sky_Play::~Sky_Play()
{
	ReleaseModel();
}

// �X�V
void Sky_Play::Update()
{
	float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ��]
	SetRotate(SimpleMath::Vector3(0.0f, timer * ROTATE_SPEED, 0.0f));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void Sky_Play::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}