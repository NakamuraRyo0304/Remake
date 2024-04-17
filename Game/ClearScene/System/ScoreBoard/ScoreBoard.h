/*
 *  @File   ScoreBoard.h
 *  @Brief  ゲームのスコアを表示する。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SCOREBOARD
#define SCOREBOARD

class DrawNumber;
class ScoreBoard
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
	// 数値を設定
	void SetNumber(const int& num) { m_number = num; }

	// コンストラクタ
	ScoreBoard();
	// デストラクタ
	~ScoreBoard();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, double span);
	// 描画
	void Draw();

private:

	// １スプライトのサイズ
	static const UINT SIZE;

private:

	// 数字を描画する
	std::unique_ptr<DrawNumber> m_nums[2];
	// 座標
	DirectX::SimpleMath::Vector2 m_position;
	// 色
	DirectX::SimpleMath::Vector4 m_color;
	// 数値
	int m_number;

};

#endif // SCOREBOARD