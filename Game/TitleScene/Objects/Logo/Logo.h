/*
 *  @File   Logo.h
 *  @Brief  タイトルロゴ。
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

class Logo
{
private:

	// 画面比率
	DirectX::SimpleMath::Vector2 m_screenRate;

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
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

};

#endif // LOGO