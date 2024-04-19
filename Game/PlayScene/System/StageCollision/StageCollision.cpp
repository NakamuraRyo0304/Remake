/*
 *	@File	StageCollision.cpp
 *	@Brief	�X�e�[�W�̓����蔻��B
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "StageCollision.h"

// �萔�̐ݒ�
const float StageCollision::RADIUS = 1.0f;          // �����蔻����s�����a

// �R���X�g���N�^
StageCollision::StageCollision()
{
}

// �f�X�g���N�^
StageCollision::~StageCollision()
{
    m_objects.clear();
}

// ������
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

// �X�V
void StageCollision::Update(Player* player)
{
    // ����p�v���C�����W��ۑ�
    SimpleMath::Vector3 playerPos = player->GetPosition();
    SimpleMath::Vector3 playerScale = player->GetScale() * 2;

    // �I�u�W�F�N�g�̔���
    for (auto& obj : m_objects)
    {
        // ��A�N�e�B�u�̃I�u�W�F�N�g�̓X�L�b�v
        if (not obj->IsActive()) continue;

        if (not UserUtility::CheckPointInSphere(playerPos, RADIUS, obj->GetPosition())) continue;
        auto side = IsCube(&playerPos, obj->GetPosition(), playerScale, obj->GetScale());

        // �ŗL�������s��
        PerformEngenProc(player, obj, playerPos, side);
    }
}

// �ŗL����
void StageCollision::PerformEngenProc(Player* player, BaseObject* block, SimpleMath::Vector3 newPos, Side side)
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
            auto newSide = IsCube(&newPos, block->GetPosition(), player->GetScale(), block->GetScale());
            player->SetFall(newSide != Side::Up ? true : false);
            player->SetPosition(newPos);
            break;
        }
        case ID::Obj_Coin:      // �R�C��
        {
            // �l�����Ă��Ȃ���Ίl���������s��
            if (not static_cast<Coin*>(block)->IsHit())
            {
                player->CountUpCoins();
                player->SetCoinHit(true);
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
    Side side = Side::None;

    // �I�u�W�F�N�g�̔��a���v�Z
    float playerRad = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;
    float blockRad = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // ���S���W�̋������v�Z
    SimpleMath::Vector3 dist = *playerPos - blockPos;
    SimpleMath::Vector3 distabs = UserUtility::AbsVector3(dist);
    float sumRad = playerRad + blockRad;

    // ���������a��菬������ΏՓ˂Ƃ݂Ȃ�
    if (distabs.x < sumRad && distabs.y < sumRad && distabs.z < sumRad)
    {
        // �ǂ̖ʂɓ�������������
        SimpleMath::Vector3 overlap = static_cast<SimpleMath::Vector3>(sumRad) - distabs;

        // �������Ă���ʂ𔻒肵�ĉ����߂�
        if (std::min({ overlap.x, overlap.y, overlap.z }) == overlap.x)
        {
            side = dist.x > 0 ? Side::Left : Side::Right;
            playerPos->x += dist.x > 0 ? overlap.x : -overlap.x;
        }
        else if (std::min({ overlap.x, overlap.y, overlap.z }) == overlap.y)
        {
            side = dist.y > 0 ? Side::Down : Side::Up;
            playerPos->y += dist.y > 0 ? overlap.y : -overlap.y;
        }
        else
        {
            side = dist.z > 0 ? Side::Behind : Side::Front;
            playerPos->z += dist.z > 0 ? overlap.z : -overlap.z;
        }

        return side;
    }
    else
    {
        // ���������a���傫����ΏՓ˖ʂ͂Ȃ�
        return Side::None;
    }
}