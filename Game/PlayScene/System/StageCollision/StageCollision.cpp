/*
 *	@File	StageCollision.cpp
 *	@Brief	�X�e�[�W�̓����蔻��B
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "StageCollision.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float StageCollision::RADIUS = 1.0f;      // �����蔻����s�����a

//==============================================================================
// �R���X�g���N�^
//==============================================================================
StageCollision::StageCollision()
    : m_side{ Side::None }      // �Փ˖�
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
StageCollision::~StageCollision()
{
}

//==============================================================================
// �����蔻����s��
//==============================================================================
void StageCollision::Update(Player* player, BlockManager* blocks)
{
    for (auto& sand : blocks->GetSandBlock())
    {
        SimpleMath::Vector3 _playerPos = player->GetPosition();
        SimpleMath::Vector3 _playerScale = player->GetScale();
        SimpleMath::Vector3 _sandPos = sand->GetPosition();
        SimpleMath::Vector3 _sandScale = sand->GetScale();

        // ���E���ɂ�铖���蔻��̃J�����O
        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _sandPos)) continue;

        // �����蔻��̎��s�F�v���C���[�E��
        m_side = IsCollision(&_playerPos, _sandPos, _playerScale, _sandScale, true);

        // �ŗL�����F�v���C���[���W�̉����߂��K�p�E�����̒�~
        player->SetFall(m_side != Side::Up ? true : false);
        player->SetPosition(_playerPos);
    }
    for (auto& coin : blocks->GetCoinBlock())
    {
        // ��A�N�e�B�u�Ȃ珈�����Ȃ�
        if (coin->IsActive() == false) continue;

        SimpleMath::Vector3 _playerPos = player->GetPosition();
        SimpleMath::Vector3 _playerScale = player->GetScale();
        SimpleMath::Vector3 _coinPos = coin->GetPosition();
        SimpleMath::Vector3 _coinScale = coin->GetScale();

        // ���E���ɂ�铖���蔻��̃J�����O
        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _coinPos)) continue;

        // �����蔻��̎��s�F�v���C���[�E�R�C��
        m_side = IsCollision(&_playerPos, _coinPos, _playerScale, _coinScale, false);

        // �ŗL�����F�R�C���̃J�E���g�A�b�v
        if (m_side != Side::None)
        {
            player->CountUpCoins();
            coin->SetActive(false);
        }
    }
}

//==============================================================================
// �����蔻��̊ȒP�ȃ`�F�b�N
//==============================================================================
StageCollision::Side StageCollision::IsCollision(SimpleMath::Vector3* playerPos, const SimpleMath::Vector3& blockPos,
    const SimpleMath::Vector3& playerScale, const SimpleMath::Vector3& blockScale, bool push)
{
    // �Փ˖ʂ�������
    Side _side = Side::None;

    // �v���C���[�̔��a���v�Z
    float _playerRadius = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;

    // �u���b�N�̔��a���v�Z
    float _blockRadius = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // �v���C���[�̒��S���W�ƃu���b�N�̒��S���W�̍����v�Z
    SimpleMath::Vector3 _diff = *playerPos - blockPos;

    // �v���C���[�ƃu���b�N�̔��a�̍��v
    float _sumRadius = _playerRadius + _blockRadius;

    // ���߂��������ׂĐ�Βl�ɕϊ�����
    SimpleMath::Vector3 _diffAbs{ std::abs(_diff.x) ,std::abs(_diff.y) ,std::abs(_diff.z) };

    // X�AY�AZ���ꂼ��̍������v���a������������Γ������Ă���
    if (_diffAbs.x < _sumRadius && _diffAbs.y < _sumRadius && _diffAbs.z < _sumRadius)
    {
        // �ǂ̖ʂɓ�������������
        SimpleMath::Vector3 _overlap = static_cast<SimpleMath::Vector3>(_sumRadius) - _diffAbs;

        // �ŏ��̏d�Ȃ�����ʂ����
        if (_overlap.x < _overlap.y && _overlap.x < _overlap.z)
        {
            if (_diff.x > 0)
            {
                // �u���b�N�̉E���Ɠ�������
                _side = Side::Left;
                if (push) playerPos->x += _overlap.x;
            }
            else
            {
                // �u���b�N�̍����Ɠ�������
                _side = Side::Right;
                if (push) playerPos->x -= _overlap.x;
            }
        }
        else if (_overlap.y < _overlap.x && _overlap.y < _overlap.z)
        {
            if (_diff.y > 0)
            {
                // �u���b�N�̏㑤�Ɠ�������
                _side = Side::Down;
                if (push) playerPos->y += _overlap.y;
            }
            else
            {
                // �u���b�N�̉����Ɠ�������
                _side = Side::Up;
                if (push) playerPos->y -= _overlap.y;
            }
        }
        else
        {
            if (_diff.z > 0)
            {
                // �u���b�N�̑O���Ɠ�������
                _side = Side::Behind;
                if (push) playerPos->z += _overlap.z;
            }
            else
            {
                // �u���b�N�̌�둤�Ɠ�������
                _side = Side::Front;
                if (push) playerPos->z -= _overlap.z;
            }
        }
    }
    else
    {
        // �������Ă��Ȃ��ꍇ�͏Փ˖ʂ����Z�b�g
        _side = Side::None;
    }

    return _side;
}