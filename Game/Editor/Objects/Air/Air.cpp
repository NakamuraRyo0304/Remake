/*
 *	@File	Air.cpp
 *	@Brief	����p�I�u�W�F�N�g�i�G�f�B�^�j�B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Air.h"

// �R���X�g���N�^
Air::Air(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Flozen.cmo", L"Resources/Models"),
	is_hit(false)		// �Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Air);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
}

// �f�X�g���N�^
Air::~Air()
{
	ReleaseModel();
}

// �X�V
void Air::Update()
{

}

// �`��
void Air::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(states);
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
	UNREFERENCED_PARAMETER(wireframe);
	UNREFERENCED_PARAMETER(option);
}