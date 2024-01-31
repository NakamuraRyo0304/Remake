/*
 *	@File	WorldMouse.cpp
 *	@Brief	���[���h�ϊ������}�E�X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/RayCast/RayCast.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "WorldMouse.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
WorldMouse::WorldMouse(SimpleMath::Matrix view, SimpleMath::Matrix proj)
    : m_view{ view }            // �r���[�s��
    , m_projection{ proj }      // �ˉe�s��
    , m_position{}              // ���W
    , m_height{}                // Y���W�̍���
{
    m_ray = std::make_unique<RayCast>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
WorldMouse::~WorldMouse()
{
    m_ray.reset();
}

//==============================================================================
// �X�V����
//==============================================================================
void WorldMouse::Update()
{
    // ���C�̍X�V
    m_ray->Update();

    // �}�E�X�g���b�N�̎擾
    auto& _input = Input::GetInstance()->GetMouseTrack();

    // �E�N���b�N�ŏ㏸
    if (_input->rightButton == Mouse::ButtonStateTracker::PRESSED)
    {
        m_height += 0.001f;
    }
    if (_input->middleButton == Mouse::ButtonStateTracker::PRESSED)
    {
        m_height -= 0.001f;
    }

    // �N�����v����
    m_height = UserUtility::Clamp(m_height, 0.0f, 5.0f);

    // ���W��ݒ�
    m_position = m_ray->GetConvertedPosition() + SimpleMath::Vector3::UnitY * m_height;
}

//==============================================================================
// �`�揈��
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}