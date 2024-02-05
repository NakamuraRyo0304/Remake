/*
 *	@File	StageCollision.cpp
 *	@Brief	�X�e�[�W�̓����蔻��B
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "StageCollision.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float StageCollision::RADIUS = 1.0f;          // �����蔻����s�����a
const float StageCollision::SPIKE_RADIUS = 0.5f;    // ���G�l�~�[�̔��a

//==============================================================================
// �R���X�g���N�^
//==============================================================================
StageCollision::StageCollision()
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
    ////////////////////////////////////////////////////////////////////////////////////////////
    //// �y�L�q���[���z                                                                     ////
    ////  �@������s���u���b�N����ł͂Ȃ������m�F����                                      ////
    ////                                                                                    ////
    ////  �A���E���ɂ�铖���蔻��̃J�����O���s��                                          ////
    ////  �֐��FUserUtility::CheckPointInSphere(�v���C�����W, �͈�, �I�u�W�F���W)           ////
    ////                                                                                    ////
    ////  �B�����蔻��̎��s���s��                                                          ////
    ////  �֐��FIsCollision(�v���C�����W,�I�u�W�F���W,�v���C���T�C�Y,�I�u�W�F�T�C�Y)        ////
    ////                                                                                    ////
    ////  �C�ŗL�������s��                                                                  ////
    ////  �����߂��̓K�p��I�u�W�F�N�g���Ƃ̏���                                            ////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // ����p�v���C�����W��ۑ�
    SimpleMath::Vector3 _playerPos = player->GetPosition();
    SimpleMath::Vector3 _playerScale = player->GetScale() * 2;

    // ���u���b�N
    if (not blocks->GetSandBlock().empty())
    {
        for (auto& sand : blocks->GetSandBlock())
        {
            SimpleMath::Vector3 _pos = sand->GetPosition();
            SimpleMath::Vector3 _scale = sand->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCollision(&_playerPos, _pos, _playerScale, _scale);

            // �ŗL�����F�v���C���[���W�̉����߂��K�p�E�����̒�~
            player->SetFall(_side != Side::Up ? true : false);
            player->SetPosition(_playerPos);
        }
    }
    // �_�u���b�N
    if (not blocks->GetCloudBlock().empty())
    {
        for (auto& cloud : blocks->GetCloudBlock())
        {
            SimpleMath::Vector3 _pos = cloud->GetPosition();
            SimpleMath::Vector3 _scale = cloud->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCollision(&_playerPos, _pos, _playerScale, _scale);

            // �ŗL�����F�_�̈ړ��E�v���C���[�̉����o��
            player->SetFall(_side != Side::Up ? true : false);
            if (_side != Side::None)
            {
                cloud->SetHitFlag(true);
                IsCollision(&_playerPos, cloud->GetPosition(), _playerScale, _scale);
                player->SetPosition(_playerPos);
            }
        }
    }
    // �R�C��
    if (not blocks->GetCoinBlock().empty())
    {
        for (auto& coin : blocks->GetCoinBlock())
        {
            if (coin->IsActive() == false) continue;
            SimpleMath::Vector3 _pos = coin->GetPosition();
            SimpleMath::Vector3 _scale = coin->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCollision(&_playerPos, _pos, _playerScale, _scale);

            // �ŗL�����F�R�C���̃J�E���g�A�b�v
            if (_side != Side::None)
            {
                player->CountUpCoins();
                coin->SetActive(false);
            }
        }
    }
    // �S�[���I�u�W�F�N�g
    if (not blocks->GetGoalObject().empty())
    {
        for (auto& goal : blocks->GetGoalObject())
        {
            SimpleMath::Vector3 _pos = goal->GetPosition();
            SimpleMath::Vector3 _scale = goal->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCollision(&_playerPos, _pos, _playerScale, _scale);

            // �ŗL�����F�S�[�������ON
            if (_side != Side::None)
            {
                goal->OnHitFlag();
            }
        }
    }
    // ���I�u�W�F�N�g
    if (not blocks->GetSpikeEnemy().empty())
    {
        for (auto& spike : blocks->GetSpikeEnemy())
        {
            SimpleMath::Vector3 _pos = spike->GetPosition();
            SimpleMath::Vector3 _scale = spike->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, SPIKE_RADIUS, _pos)) continue;
            auto _side = IsCollision(&_playerPos, _pos, _playerScale, _scale);

            // �ŗL�����F�X�p�C�N�ɏՓ˒ʒm�𑗂�E�v���C�����E��
            if (_side != Side::None)
            {
                spike->SetHitFlag(true);
                player->SetDeath(true);
            }
        }
    }
}

//==============================================================================
// �����蔻��̊ȒP�ȃ`�F�b�N
//==============================================================================
StageCollision::Side StageCollision::IsCollision(SimpleMath::Vector3* playerPos, const SimpleMath::Vector3& blockPos,
    const SimpleMath::Vector3& playerScale, const SimpleMath::Vector3& blockScale)
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

    // ��Βl�ϊ�
    SimpleMath::Vector3 _diffAbs = UserUtility::AbsVector3(_diff);

    // XYZ���ꂼ��̍������v���a������������Γ������Ă���
    if (_diffAbs.x < _sumRadius && _diffAbs.y < _sumRadius && _diffAbs.z < _sumRadius)
    {
        // �ǂ̖ʂɓ�������������
        SimpleMath::Vector3 _overlap = static_cast<SimpleMath::Vector3>(_sumRadius) - _diffAbs;

        // �ŏ��̏d�Ȃ�����ʂ����
        if (std::min({ _overlap.x, _overlap.y, _overlap.z }) == _overlap.x)
        {
            _side = _diff.x > 0 ? Side::Left : Side::Right;
            playerPos->x += _diff.x > 0 ? _overlap.x : -_overlap.x;
        }
        else if (std::min({ _overlap.x, _overlap.y, _overlap.z }) == _overlap.y)
        {
            _side = _diff.y > 0 ? Side::Down : Side::Up;
            playerPos->y += _diff.y > 0 ? _overlap.y : -_overlap.y;
        }
        else
        {
            _side = _diff.z > 0 ? Side::Behind : Side::Front;
            playerPos->z += _diff.z > 0 ? _overlap.z : -_overlap.z;
        }
    }
    else
    {
        // �������Ă��Ȃ��ꍇ�͏Փ˖ʂ����Z�b�g
        _side = Side::None;
    }

    return _side;
}