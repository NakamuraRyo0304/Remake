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
public:

	// 色を取得する
	DirectX::SimpleMath::Vector4 GetColor() const { return m_color; }
	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// コンストラクタ
	Logo(DirectX::SimpleMath::Vector2 scRate);
	// デストラクタ
	~Logo();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate);
	// 描画
	void Draw();

private:

	// 画像サイズ
	static const RECT_U SIZE;

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

};

#endif // LOGO