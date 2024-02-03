/*
 *	@File	Sky_Select.h
 *	@Brief	スカイドームオブジェクト。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SKY_SELECT
#define SKY_SELECT

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Sky_Select : public IGameObject
{
private:

	// 回転速度
	static const float ROTATE_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Sky_Select();
	~Sky_Select();

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

};

#endif // SKY_SELECT