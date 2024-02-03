/*
 *	@File	Player.h
 *	@Brief	プレイヤー。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYER
#define PLAYER

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

//==============================================================================
// プレイヤーのパーツ
//==============================================================================
#include "Parts/Head.h"

class Player : public IGameObject
{
private:

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

private:

	// 頭
	std::unique_ptr<Head> m_head;

private:

	// 最大のパス数
	static const int MAX_PATH_NUM;

	// 最高速度
	static const float MAX_SPEED;

	// 最高速で移動する範囲
	static const float MS_RADIUS;

	// 到着範囲
	static const float ARRIVE_RADIUS;

	// 目的地到着の諦め時間
	static const float GIVEUP_TIME;

	// 死亡ライン
	static const float DEATH_LINE;

	// 死亡時の回転
	static const float DEATH_ROTATE;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Player();
	~Player();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) override;

public:

	// フォローパスを設定
	void PushBackFollowPath(DirectX::SimpleMath::Vector3 path);

	// 現在格納しているパスの数を取得
	const std::vector<DirectX::SimpleMath::Vector3>& GetGoalPoints() { return m_goalPoints; }
	// 格納しているパスを全削除
	void ResetGoalPosition() { m_goalPoints.clear(); }

	// コイン枚数を取得
	const int& GetCoinNum() { return m_coinNum; }
	// コイン枚数をカウントアップ
	void CountUpCoins() { m_coinNum++; }

	// 落下フラグを取得
	const bool& IsFall() { return is_fall; }
	// 落下フラグを設定
	void SetFall(const bool& isFall) { is_fall = isFall; }

	// 死亡フラグを取得
	const bool& IsDeath() { return is_death; }
	// 死亡フラグを設定
	void SetDeath(const bool& isDeath) { is_death = isDeath; }
};

#endif // PLAYER