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
public:

	// ワールドマウスの座標を取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

	// プレイモードにする
	void ToPlayMode() { is_playing = true; }
	// エディタモードにする
	void ToEditMode() { is_playing = false; }

	// コンストラクタ
	WorldMouse();
	// デストラクタ
	~WorldMouse();
	// 更新
	void Update();
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// 最高高度
	static const float MAX_HEIGHT;
	// プレイ時の高さ
	static const float PLAY_HEIGHT;

private:

	// レイ
	std::unique_ptr<RayCast> m_ray;
	// ワールドマウスの座標
	DirectX::SimpleMath::Vector3 m_position;
	// 高さ
	int m_height;
	// プレイモード
	bool is_playing;

};

#endif // WORLDMOUSE