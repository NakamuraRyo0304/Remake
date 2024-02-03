/*
 *	@File	Head.cpp
 *	@Brief	�v���C���[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Head.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Head::Head()
	: IGameObject(L"Resources/Models/Head.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Head::~Head()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Head::Update()
{
	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Head::Draw(ID3D11DeviceContext1* context, CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(0.5f);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}