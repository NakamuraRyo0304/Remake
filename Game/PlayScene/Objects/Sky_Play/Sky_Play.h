/*
 *	@File	Sky_Play.h
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SKY_PLAY
#define SKY_PLAY

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class Sky_Play : public IGameObject
{
public:

	// コンストラクタ
	Sky_Play();
	// デストラクタ
	~Sky_Play();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// 回転速度
	static const float ROTATE_SPEED;

};

#endif // SKY_PLAY