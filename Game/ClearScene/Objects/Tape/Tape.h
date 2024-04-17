/*
 *  @File   Tape.h
 *  @Brief  テープ。
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TAPE
#define TAPE

class DrawSprite;
class Tape
{
public:

	// コンストラクタ
	Tape();
	// デストラクタ
	~Tape();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, float rotate);
	// 描画
	void Draw();

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;
	// 座標
	DirectX::SimpleMath::Vector2 m_position;
	// 画像拡大率
	DirectX::SimpleMath::Vector2 m_rate;
	// 画面比率
	DirectX::SimpleMath::Vector2 m_scRate;

};

#endif // TAPE