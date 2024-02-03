/*
 *	@File	Logo.h
 *	@Brief	タイトルロゴオブジェクト。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Logo : public IGameObject
{
private:

	// 移動位置奥
	static const DirectX::SimpleMath::Vector3 MOVE_POS;

	// モデルのサイズ
	static const float MODEL_SCALE;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Logo();
	~Logo();

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

#endif // LOGO