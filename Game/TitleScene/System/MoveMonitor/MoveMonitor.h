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
public:

	// 動作状態を取得
	bool IsMove() const { return is_moveMouse; }

	// コンストラクタ
	MoveMonitor();
	// デストラクタ
	~MoveMonitor();
	// 更新
	void Update();

private:

	// マウス動作通知
	bool is_moveMouse;
	// 長さ
	float m_length;

};

#endif // MOVEMONITOR