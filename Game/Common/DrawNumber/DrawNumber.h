/*
 *  @File   DrawNumber.h
 *  @Brief  数字の描画クラス。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWNUMBER
#define DRAWNUMBER

// スプライト描画
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class DrawNumber
{
public:

	// ディジット
	enum Digits
	{
		One,
		Ten,

		Length
	};

public:

	// 座標を取得する
	const DirectX::SimpleMath::Vector2& GetPosition() { return m_position; }
	// 座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector2& pos) { m_position = pos; }
	// 文字拡大率を取得する
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// 文字拡大率を設定する
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// 画面拡大率を設定する
	void SetScreenRate(const DirectX::SimpleMath::Vector2& rate) { m_screenRate = rate; }
	// 色を取得する
	const DirectX::SimpleMath::Vector4& GetColor() { return m_color; }
	// 色を設定する
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }

	// コンストラクタ
	DrawNumber();
	// デストラクタ
	~DrawNumber();
	// 描画
	void Draw(UINT num, Digits digits);

private:

	// スプライトのサイズ(１ブロック)
	static const UINT SIZE;

private:

	// 数字を切り取る
	RECT_U Cut(UINT num);

private:

	// スプライト
	std::unique_ptr<DrawSprite> m_sprite;
	// 座標
	DirectX::SimpleMath::Vector2 m_position;
	// 中心座標
	DirectX::SimpleMath::Vector2 m_origin;
	// 文字拡大率
	DirectX::SimpleMath::Vector2 m_rate;
	// 画面拡大率
	DirectX::SimpleMath::Vector2 m_screenRate;
	// 色
	DirectX::SimpleMath::Vector4 m_color;
	// レクト
	RECT_U m_rect;

};

#endif // DRAWNUMBER