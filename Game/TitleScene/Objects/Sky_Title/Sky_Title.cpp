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
	: IGameObject(L"Resources/Models/Sky.cmo", L"Resources/Models")
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
	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Sky_Title::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}