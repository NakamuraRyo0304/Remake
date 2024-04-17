/*
 *  @File   Goal.cpp
 *  @Brief  �S�[���I�u�W�F�N�g�B
 *  @Date   2024-02-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Goal.h"

// �R���X�g���N�^
Goal::Goal(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Goal.cmo", L"Resources/Models", position),
	is_hit(false)	// �Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Goal);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());

	// �Փ˃t���O���I�t�ɂ���
	is_hit = false;
}

// �f�X�g���N�^
Goal::~Goal()
{
	ReleaseModel();
}

// �X�V
void Goal::Update()
{
	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void Goal::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}