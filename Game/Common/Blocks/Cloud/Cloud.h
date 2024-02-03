/*
 *	@File	Cloud.h
 *	@Brief	雲ブロック。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLOUD
#define CLOUD

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Cloud : public IGameObject
{
private:

	// 到着座標
	DirectX::SimpleMath::Vector3 m_arrivePosition;

	// 衝突フラグ
	bool is_hit;

	// 到着フラグ
	bool is_arrive;

	// 落下タイマー
	float m_fallTimer;

private:

	// 回転速度
	static const float ROTATE_SPEED;

	// 落下リミット
	static const float FALL_LIMIT;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	Cloud(DirectX::SimpleMath::Vector3 position);
	~Cloud();

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

public:

	// 衝突通知
	void SetHitFlag(bool isHit) { is_hit = isHit; }

};

#endif // CLOUD