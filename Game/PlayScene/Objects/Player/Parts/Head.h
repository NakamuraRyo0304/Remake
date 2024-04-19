/*
 *	@File	Head.h
 *	@Brief	プレイヤー頭。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef HEAD
#define HEAD

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"
// プレイヤーステート
#include "../MoveStates.h"

class Timer;
class Head : public BaseObject
{
public:

	// ステートを設定する
	void SetStatus(const MoveStates& status) { m_states = status; }

	// コンストラクタ
	Head();
	// デストラクタ
	~Head();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// モデルのスケール
	static const float SCALE;
	// 首振りの強さ
	static const float ROT_POWER;


private:

	// プレイヤーステート
	MoveStates m_states;
	// タイマー
	std::unique_ptr<Timer> m_timer;

};

#endif // HEAD