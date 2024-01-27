/*
 *	@File	Sand.h
 *	@Brief	砂ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SAND
#define SAND

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Sand : public IGameObject
{
private:

	// 衝突フラグ
	bool is_hit;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Sand(DirectX::SimpleMath::Vector3 position);
	~Sand();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) override;

public:

	// 衝突を通知する
	void NotificateHit(const bool& is) { is_hit = is; }

};

#endif // SAND