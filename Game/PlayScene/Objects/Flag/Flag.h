/*
 *	@File	Flag.h
 *	@Brief	旗オブジェクト
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAG
#define FLAG

 //==============================================================================
 // 親オブジェクトクラス
 //==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Flag : public IGameObject
{
private:

	// 落下位置
	DirectX::SimpleMath::Vector3 m_droppedPosition;

	// 到着フラグ
	bool is_arrive;

private:

	// 到着みなし値
	static const float CLOSED_MATCH;

	// 落下速度
	static const float FALL_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="start">開始座標</param>
	/// <param name="dropped">落下座標</param>
	/// <returns>なし</returns>
	Flag(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& dropped);
	~Flag();

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
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

	// 到着状況を取得(到着したらTrue)
	bool IsArrive() { return is_arrive; }
};

#endif // FLAG