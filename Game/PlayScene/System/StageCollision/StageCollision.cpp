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
const float StageCollision::SPIKE_RADIUS = 0.5f;    // 棘エネミーの半径

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
}

//==============================================================================
// 当たり判定を行う
//==============================================================================
void StageCollision::Update(Player* player, BlockManager* blocks)
{
    ////////////////////////////////////////////////////////////////////////////////////////////
    //// 【記述ルール】                                                                     ////
    ////  �@判定を行うブロックが空ではないかを確認する                                      ////
    ////                                                                                    ////
    ////  �A境界球による当たり判定のカリングを行う                                          ////
    ////  関数：UserUtility::CheckPointInSphere(プレイヤ座標, 範囲, オブジェ座標)           ////
    ////                                                                                    ////
    ////  �B当たり判定の実行を行う                                                          ////
    ////  関数：IsCollision(プレイヤ座標,オブジェ座標,プレイヤサイズ,オブジェサイズ)        ////
    ////                                                                                    ////
    ////  �C固有処理を行う                                                                  ////
    ////  押し戻しの適用やオブジェクトごとの処理                                            ////
    ////////////////////////////////////////////////////////////////////////////////////////////

    // 操作用プレイヤ座標を保存
    SimpleMath::Vector3 _playerPos = player->GetPosition();
    SimpleMath::Vector3 _playerScale = player->GetScale() * 2;

    // 氷ブロック
    if (not blocks->GetFlozens().empty())
    {
        for (auto& flozen : blocks->GetFlozens())
        {
            SimpleMath::Vector3 _pos = flozen->GetPosition();
            SimpleMath::Vector3 _scale = flozen->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：プレイヤー座標の押し戻し適用・落下の停止
            player->SetFall(_side != Side::Up ? true : false);
            player->SetPosition(_playerPos);
        }
    }
    // 雲ブロック
    if (not blocks->GetClouds().empty())
    {
        for (auto& cloud : blocks->GetClouds())
        {
            SimpleMath::Vector3 _pos = cloud->GetPosition();
            SimpleMath::Vector3 _scale = cloud->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：雲の移動・プレイヤーの押し出し
            player->SetFall(_side != Side::Up ? true : false);
            if (_side != Side::None)
            {
                cloud->SetHitFlag(true);
                IsCube(&_playerPos, cloud->GetPosition(), _playerScale, _scale);
                player->SetPosition(_playerPos);
            }
        }
    }
    // コイン
    if (not blocks->GetCoins().empty())
    {
        for (auto& coin : blocks->GetCoins())
        {
            if (coin->IsHit()) continue;

            SimpleMath::Vector3 _pos = coin->GetPosition();
            SimpleMath::Vector3 _scale = coin->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：コインのカウントアップ
            if (_side != Side::None)
            {
                player->CountUpCoins();
                coin->SetHitFlag(true);
            }
        }
    }
    // ゴールオブジェクト
    if (not blocks->GetGoals().empty())
    {
        for (auto& goal : blocks->GetGoals())
        {
            SimpleMath::Vector3 _pos = goal->GetPosition();
            SimpleMath::Vector3 _scale = goal->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：ゴール判定をON
            if (_side != Side::None)
            {
                goal->OnHitFlag();
            }
        }
    }
    // 棘オブジェクト
    if (not blocks->GetSpikes().empty())
    {
        for (auto& spike : blocks->GetSpikes())
        {
            SimpleMath::Vector3 _pos = spike->GetPosition();
            SimpleMath::Vector3 _scale = spike->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, SPIKE_RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：スパイクに衝突通知を送る・プレイヤを殺す
            if (_side != Side::None)
            {
                spike->SetHitFlag(true);
                player->SetDeath(true);
            }
        }
    }
    // リフトブロック
    if (not blocks->GetLifts().empty())
    {
        for (auto& lift : blocks->GetLifts())
        {
            SimpleMath::Vector3 _pos = lift->GetPosition();
            SimpleMath::Vector3 _scale = lift->GetScale();
            if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _pos)) continue;
            auto _side = IsCube(&_playerPos, _pos, _playerScale, _scale);

            // 固有処理：落下防止
            player->SetFall(_side != Side::Up ? true : false);
            player->SetPosition(_playerPos);
        }
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
    float _playerRadius = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;
    float _blockRadius = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // 中心座標の距離を計算
    SimpleMath::Vector3 _diff = *playerPos - blockPos;
    SimpleMath::Vector3 _diffAbs = UserUtility::AbsVector3(_diff);
    float _sumRadius = _playerRadius + _blockRadius;

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