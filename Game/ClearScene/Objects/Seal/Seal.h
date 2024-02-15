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
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

	// 座標/拡大率
	DirectX::SimpleMath::Vector2 m_position, m_rate, m_scRate;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="path">シールに使う画像パス</param>
	/// <returns>なし</returns>
	Seal(const wchar_t* path);
	~Seal();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="rate">スプライト拡大率</param>
	/// <param name="scRate">スクリーン拡大率</param>
	/// <param name="rotate">回転量</param>
	/// <returns>なし</returns>
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, float rotate);

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();
};

#endif // SEAL