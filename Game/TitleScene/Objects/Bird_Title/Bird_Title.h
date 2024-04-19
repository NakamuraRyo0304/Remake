/*
 *	@File	Bird_Title.h
 *	@Brief	タイトルに表示するトリ。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BIRD_TITLE
#define BIRD_TITLE

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Bird_Title : public BaseObject
{
public:

	// コンストラクタ
	Bird_Title();
	// デストラクタ
	~Bird_Title();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// スケール
	static const float BIRD_SCALE;

};

#endif // STAGE_TITLE