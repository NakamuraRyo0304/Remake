/*
 *  @File   Seal.h
 *  @Brief  シール。
 *  @Date   2024-02-15
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SEAL
#define SEAL

class DrawSprite;
class Seal
{
public:

	// コンストラクタ
	Seal(const wchar_t* path);
	// デストラクタ
	~Seal();
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

#endif // SEAL