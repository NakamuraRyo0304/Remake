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

	// ワールドマウスの座標
	DirectX::SimpleMath::Vector3 m_position;

	// 高さ
	int m_height;

	// プレイモード
	bool is_playing;

private:

	// 最高高度
	static const float MAX_HEIGHT;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	WorldMouse();
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

	// プレイモードにする
	void ToPlayMode() { is_playing = true; }
	// エディタモードにする
	void ToEditMode() { is_playing = false; }
};

#endif // WORLDMOUSE