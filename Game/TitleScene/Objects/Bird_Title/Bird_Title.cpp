/*
 *	@File	Bird_Title.cpp
 *	@Brief	�^�C�g���ɕ\������g���B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Bird_Title.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Bird_Title::RESTART_LINE = -10.0f;
const float Bird_Title::BIRD_SCALE = 2.0f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Bird_Title::Bird_Title()
	: IGameObject(L"Resources/Models/Bird.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Back_Bird);
	SetWeight(NON_WEIGHT);

	SetPosition(SimpleMath::Vector3(0.0f, 30.0f, -5.0f));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * BIRD_SCALE);
	SetInitialScale(GetScale());

	// X�������_���ɕύX
	RandomXPosition();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Bird_Title::~Bird_Title()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Bird_Title::Update()
{
	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// ����
	SetPosition(GetPosition() - SimpleMath::Vector3::UnitY * 0.1f);

	// ���C����艺�ɍs������ăX�^�[�g
	if (GetPosition().y < RESTART_LINE)
	{
		RandomXPosition();
	}

	// ��]
	SetRotate(SimpleMath::Vector3::UnitX * _timer +
		SimpleMath::Vector3::UnitY * _timer + SimpleMath::Vector3::UnitZ * sinf(_timer));

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Bird_Title::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}

//==============================================================================
// �����_����X���W���Ē��I����
//==============================================================================
void Bird_Title::RandomXPosition()
{
	// �����_���ȍ��W���w��
	float _x = static_cast<float>(UserUtility::Random(-10.0, 10.0));

	// ���W���Z�b�g����
	SetPosition(GetInitialPosition() + SimpleMath::Vector3::UnitX * _x);
}
