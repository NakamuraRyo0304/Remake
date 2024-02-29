/*
 *	@File	Spike.cpp
 *	@Brief	���I�u�W�F�N�g(�G)�B
 *	@Date	2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Spike.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Spike::EATING_SPEED = XMConvertToRadians(15.0f);	// �ߐH���̉�]���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Spike::Spike(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Spike.cmo", L"Resources/Models", position)
	, is_hit{ false }				                            // �Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Spike);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Spike::~Spike()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Spike::Update()
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not IsActive()) return;

	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());
	float _12Sin = (sinf(_timer) + 1) * 0.5f + 1;

	// �Փ˒ʒm����������s
	if (is_hit)
	{
		// �����̓�{�ɂ���
		SetScale(UserUtility::Lerp(GetScale(), GetInitialScale() * 2, 0.05f));

		// �����ŉ�]����i�ߐH�j
		SetRotate(GetRotate() + SimpleMath::Vector3::UnitY * EATING_SPEED * _12Sin);
	}
	else
	{
		// �Փ˂��Ă��Ȃ��Ԃ͂����߂�
		SetScale(GetInitialScale() * _12Sin * 0.5f);
	}

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Spike::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not IsActive()) return;

	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}