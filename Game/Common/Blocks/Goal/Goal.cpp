/*
 *  @File   Goal.cpp
 *  @Brief  �S�[���I�u�W�F�N�g�B
 *  @Date   2024-02-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Goal.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Goal::Goal(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Goal.cmo", L"Resources/Models", position)
	, is_hit{ false }	// �Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Goal);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());

	// �Փ˃t���O���I�t�ɂ���
	is_hit = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Goal::~Goal()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Goal::Update()
{
	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Goal::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}