/*
 *  @File   UI_PlayArea.h
 *  @Brief  プレイシーンのUIのエリア。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAYAREA
#define UI_PLAYAREA

class DrawSprite;
class UI_PlayArea
{
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;
	DirectX::SimpleMath::Vector2 m_position, m_rate;
	DirectX::SimpleMath::Vector4 m_color;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	UI_PlayArea();
	~UI_PlayArea();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="pos">座標</param>
	/// <param name="color">文字色</param>
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

	// 座標を取得
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// 色を取得
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// 色を設定
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

};

#endif // UI_PLAYAREA