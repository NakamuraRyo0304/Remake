/*
 *	@File	Air.h
 *	@Brief	判定用オブジェクト（エディタ）。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef AIR
#define AIR

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Air : public IGameObject
{
private:

	// 衝突フラグ
	bool is_hit;

	// アクティブフラグ
	bool is_active;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Air(DirectX::SimpleMath::Vector3 position);
	~Air();

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
		ShaderLambda option = nullptr) final;

public:

	// 衝突を通知する
	void NotificateHit(const bool& is) { is_hit = is; }

	// アクティブフラグを切り替える
	void SetActive(const bool flag) { is_active = flag; }

};

#endif // AIR