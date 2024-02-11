/*
 *  @File   DrawNumber.h
 *  @Brief  数字の描画クラス。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWNUMBER
#define DRAWNUMBER

//==============================================================================
// スプライト描画
//==============================================================================
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class DrawNumber
{
private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;

	// 座標・中心位置
	DirectX::SimpleMath::Vector2 m_position, m_origin;

	// 拡大率
	DirectX::SimpleMath::Vector2 m_rate;

	// 色
	DirectX::SimpleMath::Vector4 m_color;

	// レクト
	RECT_U m_rect;


private:

	// スプライトのサイズ(１ブロック)
	static const UINT SIZE;

public:

	// ディジット
	enum Digits
	{
		One,
		Ten,

		Length
	};

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	DrawNumber();
	~DrawNumber();

	/// <summary>
	/// 数字を描画する
	/// </summary>
	/// <param name="num">数字</param>
	/// <param name="digits">桁数</param>
	/// <returns>なし</returns>
	void Draw(UINT num, Digits digits);

private:

	/// <summary>
	/// 数字を切り取る
	/// </summary>
	/// <param name="num">数字</param>
	/// <returns>レクト</returns>
	RECT_U Cut(UINT num);

public:

	// 座標を取得する
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// 座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// 拡大率を取得する
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// 拡大率を設定する
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// 色を取得する
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

};

#endif // DRAWNUMBER