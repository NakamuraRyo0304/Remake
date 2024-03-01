/*
 *	@File	StageCollision.cpp
 *	@Brief	ステージの当たり判定。
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "StageCollision.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float StageCollision::RADIUS = 1.0f;          // 当たり判定を行う半径

//==============================================================================
// コンストラクタ
//==============================================================================
StageCollision::StageCollision()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
StageCollision::~StageCollision()
{
    m_objects.clear();
}

//==============================================================================
// 初期化関数
//==============================================================================
void StageCollision::Initialize(BlockManager* blocks)
{
    // オブジェクトの追加
    for (auto& obj : blocks->GetFlozens()) m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetClouds())  m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetCoins())   m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetGoals())   m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetSpikes())  m_objects.push_back(obj.get());
    for (auto& obj : blocks->GetLifts())   m_objects.push_back(obj.get());
}

//==============================================================================
// 当たり判定を行う
//==============================================================================
void StageCollision::Update(Player* player)
{
    // 操作用プレイヤ座標を保存
    SimpleMath::Vector3 _playerPos = player->GetPosition();
    SimpleMath::Vector3 _playerScale = player->GetScale() * 2;

    // オブジェクトの判定
    for (auto& obj : m_objects)
    {
        // 非アクティブのオブジェクトはスキップ
        if (not obj->IsActive()) continue;

        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, obj->GetPosition())) continue;
        auto _side = IsCube(&_playerPos, obj->GetPosition(), _playerScale, obj->GetScale());

        // 固有処理を行う
        PerformEngenProc(player, obj, _playerPos, _side);
    }
}

//==============================================================================
// 固有処理
//==============================================================================
void StageCollision::PerformEngenProc(Player* player, IGameObject* block, SimpleMath::Vector3 newPos, Side side)
{
    // 衝突がなければ処理をしない
    if (side == Side::None) return;

    switch (block->GetID())
    {
        case ID::Obj_Flozen:    // 氷床ブロック
        case ID::Obj_Lift:      // リフトブロック
        {
            // 着地処理を行う
            player->SetFall(side != Side::Up ? true : false);
            player->SetPosition(newPos);
            break;
        }
        case ID::Obj_Cloud:     // 雲ブロック
        {
            // 着地処理を行い、雲を動かす
            static_cast<Cloud*>(block)->SetHitFlag(side != Side::Up ? true : false);
            auto _side = IsCube(&newPos, block->GetPosition(), player->GetScale(), block->GetScale());
            player->SetFall(_side != Side::Up ? true : false);
            player->SetPosition(newPos);
            break;
        }
        case ID::Obj_Coin:      // コイン
        {
            // 獲得していなければ獲得処理を行う
            if (not static_cast<Coin*>(block)->IsHit())
            {
                player->CountUpCoins();
            }
            static_cast<Coin*>(block)->SetHitFlag(true);
            break;
        }
        case ID::Obj_Goal:      // ゴール
        {
            // ゴール処理を行う
            static_cast<Goal*>(block)->OnHitFlag();
            break;
        }
        case ID::Obj_Spike:     // スパイク
        {
            // スパイクに当たれば死亡させる
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
// 立方体の当たり判定
//==============================================================================
StageCollision::Side StageCollision::IsCube(SimpleMath::Vector3* playerPos, const SimpleMath::Vector3& blockPos,
    const SimpleMath::Vector3& playerScale, const SimpleMath::Vector3& blockScale)
{
    // 衝突面を初期化
    Side _side = Side::None;

    // オブジェクトの半径を計算
    float _pRadius = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;
    float _bRadius = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // 中心座標の距離を計算
    SimpleMath::Vector3 _diff = *playerPos - blockPos;
    SimpleMath::Vector3 _diffAbs = UserUtility::AbsVector3(_diff);
    float _sumRadius = _pRadius + _bRadius;

    // 距離が半径より小さければ衝突とみなす
    if (_diffAbs.x < _sumRadius && _diffAbs.y < _sumRadius && _diffAbs.z < _sumRadius)
    {
        // どの面に当たったか判定
        SimpleMath::Vector3 _overlap = static_cast<SimpleMath::Vector3>(_sumRadius) - _diffAbs;

        // 当たっている面を判定して押し戻す
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
        // 距離が半径より大きければ衝突面はない
        return Side::None;
    }
}