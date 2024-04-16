/*
 *	@File	Cloud.cpp
 *	@Brief	�_�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "Cloud.h"

// �萔�̐ݒ�
const float Cloud::LIMIT = 3.5f;		// ���쎞��

// �R���X�g���N�^
Cloud::Cloud(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Cloud.cmo", L"Resources/Models", position),
	is_hit(false)						// �Փ˃t���O
{
	CreateModel();
	SetID(ID::Obj_Cloud);
	SetWeight(1.0f);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
    SetInitialScale(GetScale());

	// ��������
	m_timer = std::make_unique<Timer>(Timer::Mode::limited, LIMIT);
}

// �f�X�g���N�^
Cloud::~Cloud()
{
	ReleaseModel();
}

// �X�V
void Cloud::Update()
{
    // ��]�s��
    SetRotate(SimpleMath::Vector3(0.0f, XMConvertToRadians(m_timer->GetCount()), 0.0f));

    if (is_hit)
    {
		// 1�x�����X�V����
		if (m_timer->GetCount() == 0.0f)
		{
			m_timer->Start();
		}

		// �㉺������
        SetPosition(UserUtility::Lerp(GetPosition(),
			GetInitialPosition() + sinf(m_timer->GetCount()) * SimpleMath::Vector3::UnitY * 1.1f));

		// �^�C�}�[���X�V����
		m_timer->Update();
    }

	// �A���[����������߂�
	if (m_timer->Alarm())
	{
		SetPosition(UserUtility::Lerp(GetPosition(), GetInitialPosition()));
		m_timer->Reset();
		is_hit = false;
	}

    // �}�g���N�X���쐬
    CreateWorldMatrix();
}

// �`��
void Cloud::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}