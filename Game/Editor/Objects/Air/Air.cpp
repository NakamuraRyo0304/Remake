/*
 *	@File	Air.cpp
 *	@Brief	����p�I�u�W�F�N�g�i�G�f�B�^�j�B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Air.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Air::Air(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Sand.cmo", L"Resources/Models")
	, is_hit{ false }		// �Փ˃t���O
	, is_active{ true }		// �A�N�e�B�u�t���O
{
	CreateModel();
	SetID(ID::Obj_Air);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Air::~Air()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Air::Update()
{
	// ��A�N�e�B�u�͏������Ȃ�
	if (not is_active) return;

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Air::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	UNREFERENCED_PARAMETER(states);
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
	UNREFERENCED_PARAMETER(no_use_here);
}