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

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Coin::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not is_active) return;

	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}