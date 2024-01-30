/*
 *	@File	Sand.cpp
 *	@Brief	���u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Sand.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================


//==============================================================================
// �R���X�g���N�^
//==============================================================================
Sand::Sand(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Sand.cmo", L"Resources/Models", position)
	, is_hit{ false }
{
	CreateModel();
	SetID(ID::Obj_Sand);
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
Sand::~Sand()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Sand::Update()
{
	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Sand::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, GetWireFrameFlag(), no_use_here);
}