/*
 *	@File	UserUtility.h
 *	@Brief	�֐��Ȃǂ̒�`�B
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
	/// ���`��Ԃ���֐�
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">�����鎞��</param>
	/// <returns>��Ԓ��̒l</returns>
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
	/// �N�����v�֐�
	/// </summary>
	/// <param name="v">�Ώےl</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�͈͓��F�Ώےl�A�����˔j�F�ŏ��l�A����˔j�F�ő�l</returns>
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
	/// �w�肵���~�̒��ɓ_�����邩�𔻒肷��֐�
	/// </summary>
	/// <param name="center">�~�̒��S</param>
	/// <param name="radius">�~�̔��a</param>
	/// <param name="value">���肵�����_�̈ʒu</param>
	/// <returns>�͈͓���True</returns>
	inline bool CheckPointInCircle(
		DirectX::SimpleMath::Vector2 center,
		float radius,
		DirectX::SimpleMath::Vector2 value
	)
	{
		return DirectX::SimpleMath::Vector2::Distance(center, value) < radius;
	}

	/// <summary>
	/// �w�肵�����̒��ɓ_�����邩�𔻒肷��֐�
	/// </summary>
	/// <param name="center">���̒��S</param>
	/// <param name="radius">���̔��a</param>
	/// <param name="value">���肵�����_�̈ʒu</param>
	/// <returns>�͈͓���True</returns>
	inline bool CheckPointInSphere(
		DirectX::SimpleMath::Vector3 center,
		float radius,
		DirectX::SimpleMath::Vector3 value
	)
	{
		return DirectX::SimpleMath::Vector3::Distance(center, value) < radius;
	}

	/// <summary>
	/// �I�u�W�F�N�g�̐U������
	/// </summary>
	/// <param name="duration">�h��p������</param>
	/// <param name="tremor">�h�ꕝ</param>
	/// <param name="pos">�ΏۃI�u�W�F�̃|�W�V����</param>
	/// <returns>�Ȃ�</returns>
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
	/// �����Ă���x�N�g�������߂�
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="target">�Ώ�</param>
	/// <returns>�Ȃ�</returns>
	inline const DirectX::SimpleMath::Vector3 GetDirectionVector(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector3 target
	)
	{
		return target - position;
	}

	/// <summary>
	/// 0������؂�̂Ă�֐�
	/// </summary>
	/// <param name="value">�؂�̂Ă����l</param>
	/// <returns>�؂�̂ď�����̒l</returns>
	template<typename T>
	inline T Floor(T value)
	{
		return value < 0.0f ? 0.0f : value;
	}

	/// <summary>
	/// �����_���Ȓl��Ԃ�
	/// </summary>
	/// <param name="min">����</param>
	/// <param name="max">���</param>
	/// <returns>�����_���Ȓl</returns>
	inline double Random(double min, double max)
	{
		// srand���g�p���ė����������������
		static bool _first = false;
		if (!_first)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr)));
			_first = true;
		}

		// min����max�͈̔͂̃����_���ȕ��������_���𐶐�
		return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
	}

	/// <summary>
	/// �Q�l�̕��ς����߂�
	/// </summary>
	/// <param name="number1">���l1</param>
	/// <param name="number2">���l2</param>
	/// <returns>���ϒl</returns>
	template<typename T>
	inline T Average(T number1,T number2)
	{
		T _average = (number1 + number2) * static_cast<T>(0.5);

		return _average;
	}

	/// <summary>
	/// �ߎ���v����֐�
	/// </summary>
	/// <param name="number1">���l1</param>
	/// <param name="number2">���l2</param>
	/// <returns>�ߎ���v��True</returns>
	template<typename T>
	inline bool ClosedMatch(const T& number1, const T& number2)
	{
		return (fabsf(number1 - number2) < static_cast<T>(FLT_EPSILON));
	}
}
#endif // USERUTILITY