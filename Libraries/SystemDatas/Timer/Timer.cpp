/*
 *  @File   Timer.cpp
 *  @Brief  タイマー。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Timer.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Timer::Timer(Mode mode, float limitedSeconds)
	: m_count{ 0.0f }				// カウント
	, m_mode{ mode }				// モード
	, m_limits{ limitedSeconds }	// 制限時間
	, is_do{ false }				// 実行フラグ
	, is_alarm{ false }				// アラーム
{
}

//==============================================================================
// デストラクタ
//==============================================================================
Timer::~Timer()
{
}

//==============================================================================
// タイマースタート
//==============================================================================
void Timer::Start()
{
	is_do = true;
}

//==============================================================================
// 更新関数
//==============================================================================
void Timer::Update(bool updown)
{
	// 実行がオフでスキップ
	if (is_do == false) return;

	// fpsを取得
	auto _fps = DX::StepTimer::GetInstance().GetFramesPerSecond();

	// アラームがなっていなければ続ける
	{
		// カウントアップ
		if (updown == true && is_alarm == false)
		{
			m_count += 1.0f / _fps;
		}

		// カウントダウン
		if (updown == false && is_alarm == false)
		{
			m_count -= 1.0f / _fps;
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

//==============================================================================
// タイマーストップ
//==============================================================================
void Timer::Stop()
{
	is_do = false;
}
