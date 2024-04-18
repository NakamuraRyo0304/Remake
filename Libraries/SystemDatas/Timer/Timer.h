/*
 *  @File   Timer.h
 *  @Brief  タイマー。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TIMER
#define TIMER

class Timer
{
public:

	// タイマーのモード
	enum Mode
	{
		limited,		// 制限付き
		infinited,		// 無限

		length,
	};

public:

	// アラーム状況を取得
	bool Alarm() const { return is_alarm; }
	// カウントを取得
	float GetCount() const { return m_count; }

	// コンストラクタ
	Timer(Mode mode, float limitedSeconds = 0.0f);
	// デストラクタ
	~Timer();
	// タイマースタート
	void Start();
	// 更新
	void Update(bool updown = true);
	// タイマーストップ
	void Stop();
	// タイマーリセット
	void Reset() { m_count = 0.0f; }
	// 再スタート
	void ReStart();

private:

	// カウント/制限時間
	float m_count, m_limits;
	// 実行フラグ/アラーム
	bool is_do, is_alarm;
	// モード
	Mode m_mode;

};

#endif // TIMER