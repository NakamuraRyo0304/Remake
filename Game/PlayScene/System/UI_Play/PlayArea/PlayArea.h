/*
 *  @File   PlayArea.h
 *  @Brief  プレイシーンのUIのエリア。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYAREA
#define PLAYAREA

class DrawSprite;
class PlayArea
{
public:

	// 座標を取得
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// 色を取得
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// 色を設定
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// コンストラクタ
	PlayArea();
	// デストラクタ
	~PlayArea();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate);
	// 描画
	void Draw();

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprites;
	// 座標
	DirectX::SimpleMath::Vector2 m_position;
	// 拡大率
	DirectX::SimpleMath::Vector2 m_rate;
	// 色
	DirectX::SimpleMath::Vector4 m_color;

};

#endif // PLAYAREA