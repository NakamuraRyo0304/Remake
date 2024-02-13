/*
 *  @File   Timer.h
 *  @Brief  タイマー。
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TIMER
#define TIMER

#include <numeric>
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

private:

	// カウント/制限時間
	float m_count, m_limits;

	// 実行フラグ/アラーム
	bool is_do, is_alarm;

	// モード
	Mode m_mode;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mode">タイマーのモード</param>
	/// <param name="limitedSeconds">制限時間(なければ不要)</param>
	/// <returns>なし</returns>
	Timer(Mode mode, float limitedSeconds = std::numeric_limits<float>::max());
	~Timer();

	/// <summary>
	/// タイマースタート
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Start();

	/// <summary>
	/// 更新関数
	/// </summary>
	/// <param name="updown">True:カウントアップ/Down:カウントダウン(デフォルトはTrue)</param>
	/// <returns>なし</returns>
	void Update(bool updown = true);

	/// <summary>
	/// タイマーストップ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Stop();

	/// <summary>
	/// タイマーリセット
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Reset() { m_count = 0.0f; }

public:

	// リミットに達したらアラームを通知
	const bool& Alarm() { return is_alarm; }

	// カウントを取得
	const float& GetCount() { return m_count; }
};

#endif // TIMER