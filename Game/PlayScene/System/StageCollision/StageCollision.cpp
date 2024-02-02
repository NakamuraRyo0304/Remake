/*
 *	@File	StageCollision.cpp
 *	@Brief	ステージの当たり判定。
 *	@Date	2024-01-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "StageCollision.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float StageCollision::RADIUS = 1.0f;      // 当たり判定を行う半径

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
    for (auto& sand : blocks->GetSandBlock())
    {
        SimpleMath::Vector3 _playerPos = player->GetPosition();
        SimpleMath::Vector3 _playerScale = player->GetScale();
        SimpleMath::Vector3 _sandPos = sand->GetPosition();
        SimpleMath::Vector3 _sandScale = sand->GetScale();

        // 境界球による当たり判定のカリング
        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _sandPos)) continue;

        // 当たり判定の実行：プレイヤー・砂
        auto _sandFlag = IsCollision(&_playerPos, _sandPos, _playerScale, _sandScale, true);

        // 固有処理：プレイヤー座標の押し戻し適用・落下の停止
        player->SetFall(_sandFlag != Side::Up ? true : false);
        player->SetPosition(_playerPos);
    }
    for (auto& coin : blocks->GetCoinBlock())
    {
        // 非アクティブなら処理しない
        if (coin->IsActive() == false) continue;

        SimpleMath::Vector3 _playerPos = player->GetPosition();
        SimpleMath::Vector3 _playerScale = player->GetScale();
        SimpleMath::Vector3 _coinPos = coin->GetPosition();
        SimpleMath::Vector3 _coinScale = coin->GetScale();

        // 境界球による当たり判定のカリング
        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _coinPos)) continue;

        // 当たり判定の実行：プレイヤー・コイン
        auto _coinFlag = IsCollision(&_playerPos, _coinPos, _playerScale, _coinScale, false);

        // 固有処理：コインのカウントアップ
        if (_coinFlag != Side::None)
        {
            player->CountUpCoins();
            coin->SetActive(false);
        }
    }
    for (auto& cloud : blocks->GetCloudBlock())
    {
        SimpleMath::Vector3 _playerPos = player->GetPosition();
        SimpleMath::Vector3 _playerScale = player->GetScale();
        SimpleMath::Vector3 _cloudPos = cloud->GetPosition();
        SimpleMath::Vector3 _cloudScale = cloud->GetScale();

        // 境界球による当たり判定のカリング
        if (not UserUtility::CheckPointInSphere(_playerPos, RADIUS, _cloudPos)) continue;

        // 当たり判定の実行：プレイヤー・雲
        auto _cloudFlag = IsCollision(&_playerPos, _cloudPos, _playerScale, _cloudScale, true);

        // 固有処理：雲の移動・プレイヤーの押し出し
        player->SetFall(_cloudFlag != Side::Up ? true : false);
        if (_cloudFlag != Side::None)
        {
            cloud->SetHitFlag(true);
            IsCollision(&_playerPos, cloud->GetPosition(), _playerScale, _cloudScale, true);
            player->SetPosition(_playerPos);
        }
    }
}

//==============================================================================
// 当たり判定の簡単なチェック
//==============================================================================
StageCollision::Side StageCollision::IsCollision(SimpleMath::Vector3* playerPos, const SimpleMath::Vector3& blockPos,
    const SimpleMath::Vector3& playerScale, const SimpleMath::Vector3& blockScale, bool push)
{
    // 衝突面を初期化
    Side _side = Side::None;

    // プレイヤーの半径を計算
    float _playerRadius = std::max({ playerScale.x, playerScale.y, playerScale.z }) * 0.5f;

    // ブロックの半径を計算
    float _blockRadius = std::max({ blockScale.x, blockScale.y, blockScale.z }) * 0.5f;

    // プレイヤーの中心座標とブロックの中心座標の差を計算
    SimpleMath::Vector3 _diff = *playerPos - blockPos;

    // プレイヤーとブロックの半径の合計
    float _sumRadius = _playerRadius + _blockRadius;

    // 求めた差をすべて絶対値に変換する
    SimpleMath::Vector3 _diffAbs{ std::abs(_diff.x) ,std::abs(_diff.y) ,std::abs(_diff.z) };

    // X、Y、Zそれぞれの差が合計半径よりも小さければ当たっている
    if (_diffAbs.x < _sumRadius && _diffAbs.y < _sumRadius && _diffAbs.z < _sumRadius)
    {
        // どの面に当たったか判定
        SimpleMath::Vector3 _overlap = static_cast<SimpleMath::Vector3>(_sumRadius) - _diffAbs;

        // 最小の重なりを持つ面を特定
        if (_overlap.x < _overlap.y && _overlap.x < _overlap.z)
        {
            if (_diff.x > 0)
            {
                // ブロックの右側と当たった
                _side = Side::Left;
                if (push) playerPos->x += _overlap.x;
            }
            else
            {
                // ブロックの左側と当たった
                _side = Side::Right;
                if (push) playerPos->x -= _overlap.x;
            }
        }
        else if (_overlap.y < _overlap.x && _overlap.y < _overlap.z)
        {
            if (_diff.y > 0)
            {
                // ブロックの上側と当たった
                _side = Side::Down;
                if (push) playerPos->y += _overlap.y;
            }
            else
            {
                // ブロックの下側と当たった
                _side = Side::Up;
                if (push) playerPos->y -= _overlap.y;
            }
        }
        else
        {
            if (_diff.z > 0)
            {
                // ブロックの前側と当たった
                _side = Side::Behind;
                if (push) playerPos->z += _overlap.z;
            }
            else
            {
                // ブロックの後ろ側と当たった
                _side = Side::Front;
                if (push) playerPos->z -= _overlap.z;
            }
        }
    }
    else
    {
        // 当たっていない場合は衝突面をリセット
        _side = Side::None;
    }

    return _side;
}