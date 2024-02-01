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
void WorldMouse::Update(const float& moveSpeed)
{
    float _fps = static_cast<float>(DX::StepTimer::GetInstance().GetFramesPerSecond());

    // ���C�̍X�V
    m_ray->Update();

    // �L�[�{�[�h�E�}�E�X�̎擾
    auto _key = Keyboard::Get().GetState();
    auto _mouse = Mouse::Get().GetState();

    // �E�N���b�N�{���V�t�g�ō~������
    if (_mouse.rightButton && _key.LeftShift)
    {
        m_height -= moveSpeed * _fps;
    }
    // �E�N���b�N�ŏ㏸
    else if (_mouse.rightButton)
    {
        m_height += moveSpeed * _fps;
    }

    // �N�����v����
    m_height = UserUtility::Clamp(m_height, 0.0f, 5.0f);

    // ���W��ݒ�
    m_position =
        m_ray->GetConvertedPosition() + SimpleMath::Vector3(0.0f, m_height, 0.0f);
}

//==============================================================================
// �`�揈��
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}