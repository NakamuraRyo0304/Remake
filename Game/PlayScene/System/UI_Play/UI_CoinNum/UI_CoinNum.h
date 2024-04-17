/*
 *  @File   UI_CoinNum.h
 *  @Brief  プレイシーンのUIのコイン数。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_COINNUM
#define UI_COINNUM

class DrawNumber;
class UI_CoinNum
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
	// コインの枚数を設定
	void SetCoinNum(const int& num) { m_coinNum = num; }
	// コインの最大数を設定
	void SetCoinMaxNum(const int& num) { m_maxCoinNum = num; }


	// コンストラクタ
	UI_CoinNum();
	// デストラクタ
	~UI_CoinNum();
	// 初期化
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate, DirectX::SimpleMath::Vector2 scRate);
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
	// コイン数
	int m_coinNum, m_maxCoinNum;
};

#endif // UI_COINNUM