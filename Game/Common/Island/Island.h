/*
 *  @File   Island.h
 *  @Brief  孤島。
 *  @Date   2024-02-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISLAND
#define ISLAND

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Island : public IGameObject
{
private:

	// 回転量
	float m_rotation;

	// 回転速度
	float m_speed;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="rate">拡大率</param>
	/// <param name="speed">回転速度</param>
	/// <returns>なし</returns>
	Island(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	~Island();

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

};

#endif // ISLAND