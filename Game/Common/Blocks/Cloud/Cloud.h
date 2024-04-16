/*
 *	@File	Cloud.h
 *	@Brief	雲ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLOUD
#define CLOUD

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class Timer;
class Cloud : public IGameObject
{
public:

	// 衝突通知
	void SetHitFlag(const bool& isHit) { is_hit = isHit; }

public:

	// コンストラクタ
	Cloud(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Cloud();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 動作時間
	static const float LIMIT;

private:

	// タイマー
	std::unique_ptr<Timer> m_timer;
	// 衝突フラグ
	bool is_hit;
};

#endif // CLOUD