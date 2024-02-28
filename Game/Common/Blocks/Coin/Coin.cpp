/*
 *	@File	Coin.cpp
 *	@Brief	�R�C���u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Coin.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Coin::ROTATE_SPEED = 30.0f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Coin::Coin(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Coin.cmo", L"Resources/Models", position)
	, is_hit{ false }		// �Փ˃t���O
	, is_active{ true }		// �A�N�e�B�u�t���O
{
	CreateModel();
	SetID(ID::Obj_Coin);
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
Coin::~Coin()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Coin::Update()
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not is_active) return;

	float _timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

	// �Փ˂�����l�����o
	if (is_hit)
	{
		// ��]���Ȃ��珬�����Ȃ�Ȃ����ɏオ��i�ŏI�I�ɏ�����j
		SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition() + SimpleMath::Vector3::UnitY * 0.5f));
		SetScale(UserUtility::Lerp(GetScale(), SimpleMath::Vector3::Zero, 0.05f));
		SetRotate(UserUtility::Lerp(GetRotate(),
			SimpleMath::Vector3::UnitY * XMConvertToRadians(_timer * ROTATE_SPEED * 2)));

		// �X�P�[����0�ɂȂ�����`���؂�
		if (GetScale().LengthSquared() < 0.01f)
		{
			is_active = false;
		}
	}
	else
	{
		SetRotate(UserUtility::Lerp(GetRotate(),
			SimpleMath::Vector3::UnitY * XMConvertToRadians(_timer * ROTATE_SPEED)));
	}

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Coin::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not is_active) return;

	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}