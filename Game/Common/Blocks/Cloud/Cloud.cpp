/*
 *	@File	Cloud.cpp
 *	@Brief	�_�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Cloud.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float Cloud::ROTATE_SPEED = 15.0f;        // ��]���x
const float Cloud::FALL_LIMIT = 180.0f;			// �������~�b�g

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Cloud::Cloud(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models", position)
	, is_hit{ false }			// �Փ˃t���O
	, is_arrive{ false }		// �����t���O
    , m_arrivePosition{}    	// �������W
    , m_fallTimer{}				// �����^�C�}�[
{
	CreateModel();
	SetID(ID::Obj_Cloud);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
    SetInitialScale(GetScale());

	// �������W
	m_arrivePosition = GetInitialPosition() + SimpleMath::Vector3::UnitY;

	// ��������
	m_fallTimer = 0.0f;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Cloud::~Cloud()
{
	ReleaseModel();
}

//==============================================================================
// �X�V����
//==============================================================================
void Cloud::Update()
{
    float timer = static_cast<float>(DX::StepTimer::GetInstance().GetTotalSeconds());

    // ��]�s��
    SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(timer * ROTATE_SPEED), 0.0f));

    if (is_hit)
    {
        // �㏸������
        SetPosition(UserUtility::Lerp(GetPosition(), m_arrivePosition, 0.1f));
		m_fallTimer++;
    }

	// �����^�C�}�[�����~�b�g���z�����猳�ɖ߂�
	if (m_fallTimer > FALL_LIMIT)
	{
		SetPosition(GetInitialPosition());

		// ���̈ʒu�ɖ߂�����^�C�}�[�����Z�b�g����
		if (GetPosition() == GetInitialPosition())
		{
			m_fallTimer = 0.0f;
			is_hit = false;
		}
	}

    // �}�g���N�X���쐬
    CreateWorldMatrix();
}


//==============================================================================
// �`�揈��
//==============================================================================
void Cloud::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}