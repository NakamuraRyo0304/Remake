/*
 *	@File	WorldMouse.h
 *	@Brief	ワールド変換したマウス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef WORLDMOUSE
#define WORLDMOUSE

class RayCast;
class WorldMouse
{
private:

	// レイ
	std::unique_ptr<RayCast> m_ray;

	// ビュー行列、射影行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// ワールドマウスの座標
	DirectX::SimpleMath::Vector3 m_position;

	// 高さ
	float m_height;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	WorldMouse(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	~WorldMouse();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	// ワールドマウスの座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
};

#endif // WORLDMOUSE