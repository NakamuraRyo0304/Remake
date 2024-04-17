/*
 *  @File   MoveMonitor.cpp
 *  @Brief  ��ʊĎ��ҁB
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MoveMonitor.h"

// �R���X�g���N�^
MoveMonitor::MoveMonitor()
	:
	m_length(),			// �ŏI����
    is_moveMouse(false) // ����ʒm�t���O�i��������True�j
{
}

// �f�X�g���N�^
MoveMonitor::~MoveMonitor()
{
}

// �X�V
void MoveMonitor::Update()
{
    auto ms = Mouse::Get().GetState();
    auto msPosition = SimpleMath::Vector2(static_cast<float>(ms.x), static_cast<float>(ms.y));

    // ���݂̃}�E�X���W��0:0�̋������v�Z
    float length = SimpleMath::Vector2::Distance(SimpleMath::Vector2::Zero, msPosition);

    // ���ȏ�̋������������ꍇ�ɒʒm�t���O�𗧂Ă�
    if (length != m_length)
    {
        is_moveMouse = true;
    }
    else
    {
        is_moveMouse = false;
    }

    // ���W����̋������X�V
    m_length = length;
}
