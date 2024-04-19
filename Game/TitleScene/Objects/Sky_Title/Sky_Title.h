/*
 *	@File	Sky_Title.h
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2023-12-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SKY_TITLE
#define SKY_TITLE

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Sky_Title : public BaseObject
{
public:

	// コンストラクタ
	Sky_Title();
	// デストラクタ
	~Sky_Title();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

};

#endif // SKY_TITLE