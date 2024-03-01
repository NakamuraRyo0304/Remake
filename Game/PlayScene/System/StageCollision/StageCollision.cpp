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
    m_objects.clear();
}

//==============================================================================
// �������֐�
//==============================================================================
void StageCollision::Initialize(BlockManager* blocks)
{
    // �I�u�W�F�N�g�̒ǉ�
    for (auto& obj : blocks->GetFlozens()) m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetClouds())  m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetCoins())   m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetGoals())   m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetSpikes())  m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetLifts())   m_objects.push_back(obj.get());
}

//==============================================================================
// �����蔻����s��
//==============================================================================
void StageCollision::Update(Player* player)
{
    // ����p�v���C�����W��ۑ�
    SimpleMath::Vector3 _playerPos = player->GetPosition();
    SimpleMath::Vector3 _playerScale = player->GetScale() * 2;

    // �I�u�W�F�N�g�̔���
    for (auto& obj : m_objects)
    {
        // ��A�N�e�B�u�̃I�u�W�F�N�g�̓X�L�b�v
        if (not obj->IsActive()) continue;

        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, obj->GetPosition())) continue;
        auto _side = IsCube(&_playerPos, obj->GetPosition(), _playerScale, obj->GetScale());

        // �ŗL�������s��
        PerformEngenProc(player, obj, _playerPos, _side);
    }
}

//==============================================================================
// �ŗL����
//==============================================================================
void StageCollision::PerformEngenProc(Player* player, IGameObject* block, SimpleMath::Vector3 newPos, Side side)
{
    // �Փ˂��Ȃ���Ώ��������Ȃ�
    if (side == Side::None) return;

    switch (block->GetID())
    {
        case ID::Obj_Flozen:    // �X���u���b�N
        case ID::Obj_Lift:      // ���t�g�u���b�N
        {
            // ���n�������s��
            player->SetFall(side != Side::Up ? true : false);
            player->SetPosition(newPos);
            break;
        }
        case ID::Obj_Cloud:     // �_�u���b�N
        {
            // ���n�������s���A�_�𓮂���
            static_cast<Cloud*>(block)->SetHitFlag(side != Side::Up ? true : false);
            auto _side = IsCube(&newPos, block->GetPosition(), player->GetScale(), block->GetScale());
            player->SetFall(_side != Side::Up ? true : false);
            player->SetPosition(newPos);
            break;
        }
        case ID::Obj_Coin:      // �R�C��
        {
            // �l�����Ă��Ȃ���Ίl���������s��
            if (not static_cast<Coin*>(block)->IsHit())
            {
                player->CountUpCoins();
            }
            static_cast<Coin*>(block)->SetHitFlag(true);
            break;
        }
        case ID::Obj_Goal:      // �S�[��
        {
            // �S�[���������s��
            static_cast<Goal*>(block)->OnHitFlag();
            break;
        }
        case ID::Obj_Spike:     // �X�p�C�N
        {
            // �X�p�C�N�ɓ�����Ύ��S������
            static_cast<Spike*>(block)->SetHitFlag(true);
            player->SetDeath(true);
            break;
        }
        default:
            player->SetFall(true);
            break;
    }
}

//==============================================================================
// �����̂̓����蔻��
//==============================================================================
StageCollision::Side StageCollision::IsCube(SimpleMath::Vector3* playerPos, const SimpleMath::Vector3& blockPos,
    const SimpleMath::Vector3& playerScale, const SimpleMath::Vector3& blockScale)
{
    // �Փ˖ʂ�������
    Side _side = Side::None;

    // �I�u�W�F�N�g�̔��a���v�Z
    float _pRadius = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;
    float _bRadius = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // ���S���W�̋������v�Z
    SimpleMath::Vector3 _diff = *playerPos - blockPos;
    SimpleMath::Vector3 _diffAbs = UserUtility::AbsVector3(_diff);
    float _sumRadius = _pRadius + _bRadius;

    // ���������a��菬������ΏՓ˂Ƃ݂Ȃ�
    if (_diffAbs.x < _sumRadius && _diffAbs.y < _sumRadius && _diffAbs.z < _sumRadius)
    {
        // �ǂ̖ʂɓ�������������
        SimpleMath::Vector3 _overlap = static_cast<SimpleMath::Vector3>(_sumRadius) - _diffAbs;

        // �������Ă���ʂ𔻒肵�ĉ����߂�
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

        return _side;
    }
    else
    {
        // ���������a���傫����ΏՓ˖ʂ͂Ȃ�
        return Side::None;
    }
}