/*
 *  @File   MoveMonitor.h
 *  @Brief  画面監視者。
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MOVEMONITOR
#define MOVEMONITOR

class MoveMonitor
{
private:

	// マウス動作通知
	bool is_moveMouse;

	// 長さ
	float m_length;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	MoveMonitor();
	~MoveMonitor();

	/// <summary>
	/// 更新関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 動作通知
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>動いたらTrue</returns>
	bool IsMove() const { return is_moveMouse; }
};

#endif // MOVEMONITOR