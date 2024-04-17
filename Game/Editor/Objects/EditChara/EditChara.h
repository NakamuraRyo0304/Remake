/*
 *	@File	EditChara.h
 *	@Brief	プレイヤー（エディタ）。
 *	@Date	2024-02-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITCHARA
#define EDITCHARA

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class EditChara : public IGameObject
{
public:

	// コンストラクタ
	EditChara(DirectX::SimpleMath::Vector3 position);
	// デストラクタ
	~EditChara();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) final;

};
#endif // EDITCHARA