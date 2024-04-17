/*
 *  @File   Timer.cpp
 *  @Brief  タイマー。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Timer.h"

// コンストラクタ
Timer::Timer(Mode mode, float limitedSeconds)
	:
	m_count(0.0f),				// カウント
	m_mode(mode),				// モード
	m_limits(limitedSeconds),	// 制限時間
	is_do(false),				// 実行フラグ
	is_alarm(false)				// アラーム
{
}

// デストラクタ
Timer::~Timer()
{
}

// タイマースタート
void Timer::Start()
{
	is_alarm = false;
	is_do = true;
}

// 更新
void Timer::Update(bool updown)
{
	// 実行がオフでスキップ
	if (is_do == false) return;

	// アラームがなっていなければ続ける
	{
		// カウントアップ
		if (updown == true && is_alarm == false)
		{
			m_count += static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());
		}

		// カウントダウン
		if (updown == false && is_alarm == false)
		{
			m_count -= static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());
		}
	}

	// 時間制限があるなら実行する
	if (m_mode == Mode::limited)
	{
		if (std::fabsf(m_count - m_limits) < 0.01f)
		{
			is_alarm = true;
			is_do = false;
		}
	}
}

// タイマーストップ
void Timer::Stop()
{
	is_do = false;
}

// 再スタート
void Timer::ReStart()
{
	Stop();
	Reset();
	Start();
}
