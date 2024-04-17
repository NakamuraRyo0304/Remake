/*
 *	@File	Flag.cpp
 *	@Brief	���I�u�W�F�N�g
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Flag.h"

// �萔�̐ݒ�
const float Flag::FALL_SPEED = 0.05f;		// �������x
const float Flag::CLOSED_MATCH = 0.1f;		// �ߎ���v

// �R���X�g���N�^
Flag::Flag(const SimpleMath::Vector3& start, const SimpleMath::Vector3& dropped)
	:
	IGameObject(L"Resources/Models/Flag.cmo", L"Resources/Models"),
	m_droppedPosition(),		            // �����ʒu
	is_arrive(false)			            // �����t���O
{
	CreateModel();
	SetID(ID::Obj_Flag);
	SetWeight(NON_WEIGHT);
	SetPosition(start);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
	SetInitialScale(GetScale());

	// �������ݒ�
	m_droppedPosition = dropped;
}

// �f�X�g���N�^
Flag::~Flag()
{
	ReleaseModel();
}

// �X�V
void Flag::Update()
{
	// �������Ă���
	SetPosition(UserUtility::Lerp(GetPosition(), m_droppedPosition, FALL_SPEED));

	// �ʒu�����肵����True
	if (std::abs(GetPosition().y - m_droppedPosition.y) < CLOSED_MATCH)
	{
		is_arrive = true;
	}

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void Flag::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}