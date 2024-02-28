/*
 *  @File   MoveMonitor.cpp
 *  @Brief  ��ʊĎ��ҁB
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MoveMonitor.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
MoveMonitor::MoveMonitor()
	: is_moveMouse{ false }		// ����ʒm�t���O�i��������True�j
	, m_length{}			    // �ŏI����
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
MoveMonitor::~MoveMonitor()
{
}

//==============================================================================
// �X�V�֐�
//==============================================================================
void MoveMonitor::Update()
{
    auto _ms = Mouse::Get().GetState();
    auto _msp = SimpleMath::Vector2(static_cast<float>(_ms.x), static_cast<float>(_ms.y));

    // ���݂̃}�E�X���W��0:0�̋������v�Z
    float _length = SimpleMath::Vector2::Distance(SimpleMath::Vector2::Zero, _msp);

    // ���ȏ�̋������������ꍇ�ɒʒm�t���O�𗧂Ă�
    if (_length != m_length)
    {
        is_moveMouse = true;
    }
    else
    {
        is_moveMouse = false;
    }

    // ���W����̋������X�V
    m_length = _length;
}
