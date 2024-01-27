/*
 *	@File	WorldMouse.cpp
 *	@Brief	���[���h�ϊ������}�E�X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/RayCast/RayCast.h"
#include "WorldMouse.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
WorldMouse::WorldMouse(SimpleMath::Matrix view, SimpleMath::Matrix proj)
    : m_view{ view }            // �r���[�s��
    , m_projection{ proj }      // �ˉe�s��
    , m_position{}              // ���W
{
    m_ray = std::make_unique<RayCast>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
WorldMouse::~WorldMouse()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void WorldMouse::Update()
{
    // ��̍X�V
    m_ray->Update();

    // ���W���擾
    m_position = m_ray->GetConvertedPosition();
}

//==============================================================================
// �`�揈��
//==============================================================================
void WorldMouse::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
    m_ray->SetMatrix(view, proj);
}