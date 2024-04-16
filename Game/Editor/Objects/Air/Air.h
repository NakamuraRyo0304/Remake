/*
 *	@File	Air.h
 *	@Brief	判定用オブジェクト（エディタ）。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef AIR
#define AIR

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class Air : public IGameObject
{
public:

	// コンストラクタ
	Air(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~Air();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;
private:

	// 衝突フラグ
	bool is_hit;

};

#endif // AIR