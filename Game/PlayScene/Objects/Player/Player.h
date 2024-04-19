/*
 *	@File	Player.h
 *	@Brief	プレイヤー。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYER
#define PLAYER

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"
// プレイヤーステート
#include "MoveStates.h"
// プレイヤーのパーツ
#include "Parts/Head.h"

class Player : public BaseObject
{
public:

	// フォローパスを取得
	std::vector<DirectX::SimpleMath::Vector3>& GetFollowPath() { return m_goalPoints; }
	// フォローパスを追加
	void AddFollowPath(const DirectX::SimpleMath::Vector3& path, const int& max);
	// 格納しているパスを全削除
	void ResetGoalPosition() { m_goalPoints.clear(); }
	// コイン枚数を取得
	int GetCoinNum() const { return m_coinNum; }
	// コイン枚数をカウントアップ
	void CountUpCoins() { m_coinNum++; }
	// コイン衝突フラグを取得
	bool IsCoinHit() const { return is_coinHit; }
	// コイン衝突フラグを設定
	void SetCoinHit(const bool& isHit) { is_coinHit = isHit; }
	// 落下フラグを取得
	bool IsFall() const { return is_fall; }
	// 落下フラグを設定
	void SetFall(const bool& isFall) { is_fall = isFall; }
	// 死亡フラグを取得
	bool IsDeath() const { return is_death; }
	// 死亡フラグを設定
	void SetDeath(const bool& isDeath) { is_death = isDeath; }

public:

	// コンストラクタ
	Player();
	// デストラクタ
	~Player();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 最高速度
	static const float MAX_SPEED;
	// 最高速で移動する範囲
	static const float RANGE;
	// 到着範囲
	static const float ARRIVE_RADIUS;
	// 目的地到着の諦め時間
	static const float GIVEUP_TIME;
	// 旋回速度
	static const float ROTATE_SPEED;
	// 重力
	static const float GRAVITY;
	// 死亡ライン
	static const float DEATH_LINE;
	// 死亡時の回転
	static const float DEATH_ROTATE;
	// モデルのスケール
	static const float SCALE;

private:

	// 頭
	std::unique_ptr<Head> m_head;
	// 目的地キュー
	std::vector<DirectX::SimpleMath::Vector3> m_goalPoints;
	// 移動量
	DirectX::SimpleMath::Vector3 m_velocity;
	// 移動ギブアップタイム
	float m_giveUpTime;
	// 所有コイン枚数
	int m_coinNum;
	// 落下フラグ
	bool is_fall;
	// 死亡フラグ
	bool is_death;
	// コイン衝突フラグ
	bool is_coinHit;

};

#endif // PLAYER