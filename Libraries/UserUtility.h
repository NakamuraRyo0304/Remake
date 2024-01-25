/*
 *	@File	UserUtility.h
 *	@Brief	関数などの定義。
 *	@Date	2023-06-01
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef USERUTILITY
#define	USERUTILITY

#include <iostream>

namespace UserUtility
{
	/// <summary>
	/// 線形補間する関数
	/// </summary>
	/// <param name="a">開始値</param>
	/// <param name="b">終了値</param>
	/// <param name="t">かかる時間</param>
	/// <returns>補間中の値</returns>
	template<typename T>
	inline T Lerp(
		T a,
		T b,
		float t
	)
	{
		return a + t * (b - a);
	}

	/// <summary>
	/// クランプ関数
	/// </summary>
	/// <param name="v">対象値</param>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>範囲内：対象値、下限突破：最小値、上限突破：最大値</returns>
	template<typename T>
	inline T Clamp(
		T v,
		T min,
		T max
	)
	{
		return v < min ? min : v > max ? max : v;
	}

	/// <summary>
	/// 指定した円の中に点があるかを判定する関数
	/// </summary>
	/// <param name="center">円の中心</param>
	/// <param name="radius">円の半径</param>
	/// <param name="value">判定したい点の位置</param>
	/// <returns>範囲内でTrue</returns>
	inline bool CheckPointInCircle(
		DirectX::SimpleMath::Vector2 center,
		float radius,
		DirectX::SimpleMath::Vector2 value
	)
	{
		return DirectX::SimpleMath::Vector2::Distance(center, value) < radius;
	}

	/// <summary>
	/// 指定した球の中に点があるかを判定する関数
	/// </summary>
	/// <param name="center">球の中心</param>
	/// <param name="radius">球の半径</param>
	/// <param name="value">判定したい点の位置</param>
	/// <returns>範囲内でTrue</returns>
	inline bool CheckPointInSphere(
		DirectX::SimpleMath::Vector3 center,
		float radius,
		DirectX::SimpleMath::Vector3 value
	)
	{
		return DirectX::SimpleMath::Vector3::Distance(center, value) < radius;
	}

	/// <summary>
	/// オブジェクトの振動処理
	/// </summary>
	/// <param name="duration">揺れ継続時間</param>
	/// <param name="tremor">揺れ幅</param>
	/// <param name="pos">対象オブジェのポジション</param>
	/// <returns>なし</returns>
	inline void ShakeObject(
		float duration,
		float tremor,
		SimpleMath::Vector3* pos
	)
	{
		int _counta = 0;
		_counta++;

		float _d = (rand() % 10) * 0.01f * tremor;

		SimpleMath::Vector3 _sav = (*pos);

		if (_counta > duration)
		{
			(*pos) = _sav;
		}
		else
		{
			(*pos).x += _d * (rand() % 3 - 1);
			(*pos).y += _d * (rand() % 3 - 1);
			(*pos).z += _d * (rand() % 3 - 1);
		}
	}

	/// <summary>
	/// 向いているベクトルを求める
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="target">対象</param>
	/// <returns>なし</returns>
	inline const DirectX::SimpleMath::Vector3 GetDirectionVector(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 target
	)
	{
		return target - position;
	}

	/// <summary>
	/// 0未満を切り捨てる関数
	/// </summary>
	/// <param name="value">切り捨てたい値</param>
	/// <returns>切り捨て処理後の値</returns>
	template<typename T>
	inline T Floor(T value)
	{
		return value < 0.0f ? 0.0f : value;
	}

	/// <summary>
	/// ランダムな値を返す
	/// </summary>
	/// <param name="min">下限</param>
	/// <param name="max">上限</param>
	/// <returns>ランダムな値</returns>
	inline double Random(double min, double max)
	{
		// srandを使用して乱数生成器を初期化
		static bool _first = false;
		if (!_first)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			_first = true;
		}

		// minからmaxの範囲のランダムな浮動小数点数を生成
		return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
	}

	/// <summary>
	/// ２値の平均を求める
	/// </summary>
	/// <param name="number1">数値1</param>
	/// <param name="number2">数値2</param>
	/// <returns>平均値</returns>
	template<typename T>
	inline T Average(T number1,T number2)
	{
		T _average = (number1 + number2) * static_cast<T>(0.5);

		return _average;
	}

	/// <summary>
	/// 近似一致判定関数
	/// </summary>
	/// <param name="number1">数値1</param>
	/// <param name="number2">数値2</param>
	/// <returns>近似一致でTrue</returns>
	template<typename T>
	inline bool ClosedMatch(const T& number1, const T& number2)
	{
		return (fabsf(number1 - number2) < static_cast<T>(FLT_EPSILON));
	}
}
#endif // USERUTILITY