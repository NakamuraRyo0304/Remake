/*
 *	@File	ColliderHelper.h
 *	@Brief	当たり判定のヘルパークラス。
 *	@Date	2023-01-09
 *  @Author NakamuraRyo
 */

#pragma once

#ifndef JUDGECUBECUBE
#define JUDGECUBECUBE

//==============================================================================
// 立方体判定(AABB)
//==============================================================================
class JudgeCubeCube
{
public:

	// 衝突面
	enum class HITBIT : UINT
	{
		None,
		Left,
		Right,
		Up,
		Down,
		Front,
		Behind,
	};

private:

	// 衝突面の保管
	HITBIT m_hit;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	JudgeCubeCube();
	~JudgeCubeCube();

	// 衝突面を取得
	HITBIT GetHitBit() { return m_hit; }

	/// <summary>
	/// 当たり判定のチェック
	/// </summary>
	/// <param name="obj1">オブジェ１</param>
	/// <param name="obj2">オブジェ２</param>
	/// <param name="sz1">サイズ１</param>
	/// <param name="sz2">サイズ２</param>
	/// <returns>なし</returns>
	void CubeCheck(DirectX::SimpleMath::Vector3* obj1, DirectX::SimpleMath::Vector3 obj2,
		DirectX::SimpleMath::Vector3 sz1, DirectX::SimpleMath::Vector3 sz2);
};

#endif // JUDGECUBECUBE

#ifndef COLLIDERHELPER
#define COLLIDERHELPER

//==============================================================================
// ファイルのインクルード
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class ColliderHelper
{
private:

	// 判定を行う半径
	float m_radius;

	// 判定を行うオブジェクト配列
	std::vector<IGameObject*> m_collisionList;

	// 衝突判定チェッカー（AABB）
	std::unique_ptr<JudgeCubeCube> m_aabbCollider;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="radius">判定の半径</param>
	/// <returns>なし</returns>
	ColliderHelper(const float& radius);
	~ColliderHelper();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// オブジェクトを追加する
	/// </summary>
	/// <param name="object">判定をするオブジェクトのポインタ</param>
	/// <returns>なし</returns>
	void AddObject(IGameObject* object);

};

#endif // COLLIDERHELPER
