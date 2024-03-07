/*
 *  @File   Logo.h
 *  @Brief  タイトルロゴ。
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

class DrawSprite;
class Logo
{
private:

	// 画面比率
	DirectX::SimpleMath::Vector2 m_screenRate;

	// スプライト描画
	std::unique_ptr<DrawSprite> m_sprite;

	// 座標
	DirectX::SimpleMath::Vector2 m_position;

	// 拡大率
	DirectX::SimpleMath::Vector2  m_rate;

	// 色
	DirectX::SimpleMath::Vector4 m_color;

private:

	// 画像サイズ
	static const RECT_U SIZE;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scRate">画面比率</param>
	/// <returns>なし</returns>
	Logo(DirectX::SimpleMath::Vector2 scRate);
	~Logo();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="color">色</param>
	/// <param name="rate">拡大率</param>
	/// <returns>なし</returns>
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate);

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw();

public:

	// 色を取得する
	DirectX::SimpleMath::Vector4 GetColor() const { return m_color; }
	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }
};

#endif // LOGO