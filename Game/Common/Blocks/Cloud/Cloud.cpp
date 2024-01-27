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
const float Cloud::ROTATE_SPEED = 15.0f;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Cloud::Cloud(SimpleMath::Vector3 position)
	: IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models")
	, is_hit{ false }			// �Փ˃t���O
	, is_arrive{ false }		// �����t���O
    , m_arrivePosition{}    	// �������W
{
	CreateModel();
	SetID(ID::Default);
	SetName(L"Cloud");
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);

	// �������W
	m_arrivePosition = GetInitialPosition() + SimpleMath::Vector3::UnitY;
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

        // ���B������t���O��OFF
        if (std::abs(GetPosition().y - m_arrivePosition.y) < 0.01f)
        {
            is_arrive = true;
        }
    }
    else
    {
        // �~��������
        SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition(), 0.1f));

        // ���̈ʒu�ɖ߂�����t���O��OFF
        if (std::abs(GetPosition().y - GetInitialPosition().y) < 0.01f)
        {
            is_arrive = false;
        }
    }

    // �}�g���N�X���쐬
    CreateWorldMatrix();
}


//==============================================================================
// �`�揈��
//==============================================================================
void Cloud::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda no_use_here)
{
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	GetModel()->Draw(_context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, false, no_use_here);
}