/*
 *	@File	Head.cpp
 *	@Brief	�v���C���[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "Head.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Head::SCALE = 0.5f;			// ���f���̃X�P�[��
const float Head::ROT_POWER = 15.0f;	// ��U��̋���

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Head::Head()
	: IGameObject(L"Resources/Models/pHead.cmo", L"Resources/Models")
	, m_states{ MoveStates::Idling }		// �A�C�h�����
{
	CreateModel();
	SetID(ID::Obj_Player);
	SetWeight(2.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One);
	SetInitialScale(GetScale());

	// �^�C�}�[�쐬
	m_timer = std::make_unique<Timer>(Timer::Mode::infinited);
	m_timer->Start();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Head::~Head()
{
	ReleaseModel();
	m_timer.reset();
}

//==============================================================================
// �X�V����
//==============================================================================
void Head::Update()
{
	m_timer->Update();

	// �A�C�h����Ԃ͂���낫��낷��
	if (m_states == MoveStates::Idling)
	{
		float _value = XMConvertToRadians(sinf(m_timer->GetCount()) * ROT_POWER);
		SetRotate(UserUtility::Lerp(GetRotate(), SimpleMath::Vector3::UnitY * _value));
	}
	else if(m_states == MoveStates::Walking)
	{
		SetRotate(UserUtility::Lerp(GetRotate(), SimpleMath::Vector3::Zero));
	}

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Head::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	SimpleMath::Matrix _scale = SimpleMath::Matrix::CreateScale(SCALE);
	GetModel()->Draw(context, states, _scale * GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}