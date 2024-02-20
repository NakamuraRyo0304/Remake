/*
 *  @File   DrawKeys.h
 *  @Brief  キー描画。
 *  @Date   2024-02-21
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWKEYS
#define DRAWKEYS

class DrawSprite;
class DrawKeys
{
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

	// 座標
	DirectX::SimpleMath::Vector2 m_position;

	// 画面拡大率、拡大率
	DirectX::SimpleMath::Vector2 m_scRate, m_rate;

	// 色
	DirectX::SimpleMath::Vector4 m_color;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="path">画像パス</param>
	/// <param name="pos">座標</param>
	/// <param name="screenRate">画面比率</param>
	/// <returns>なし</returns>
	DrawKeys(const wchar_t* path, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& screenRate);
	~DrawKeys();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();

public:

	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color){ m_color = color; }

	// 拡大率の取得
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// 拡大率の設定
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }

};

#endif // DRAWKEYS