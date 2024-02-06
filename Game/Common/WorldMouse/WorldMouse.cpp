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
// �萔�̐ݒ�
//==============================================================================
const float WorldMouse::MAX_HEIGHT = 5.0f;          // �ō����x
const float WorldMouse::PLAY_HEIGHT = 1.0f;         // �v���C���̍��x

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using MOUSE_BUTTON = Mouse::ButtonStateTracker;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
WorldMouse::WorldMouse()
    : m_position{}              // ���W
    , m_height{}                // Y���W�̍���
    , is_playing{ false }       // �f�t�H���g�̓G�f�B�^���[�h
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

    // �v���C���[�h�͍ō����x�ɂ���
    if (is_playing)
    {
        // ���W��ݒ�
        m_position = m_ray->GetConvertedPosition();
        m_position.y = PLAY_HEIGHT;
    }
    else
    {
        // �L�[�{�[�h�E�}�E�X�̎擾
        auto _key = Keyboard::Get().GetState();
        auto& _mt = Input::GetInstance()->GetMouseTrack();

        // �E�N���b�N�{���V�t�g�ō~������
        if (_mt->rightButton == MOUSE_BUTTON::PRESSED && _key.LeftShift)
        {
            m_height--;
        }
        // �E�N���b�N�ŏ㏸
        else if (_mt->rightButton == MOUSE_BUTTON::PRESSED)
        {
            m_height++;
        }

        // �N�����v����
        m_height = UserUtility::Clamp(m_height, 0, 5);

        // ���W��ݒ�(���`��Ԉړ�)
        m_position = m_ray->GetConvertedPosition();
        m_position.y = static_cast<float>(m_height);
    }
}

//==============================================================================
// �`�揈��
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}