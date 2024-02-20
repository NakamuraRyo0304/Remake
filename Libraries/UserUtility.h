/*
 *	@File	UserUtility.h
 *	@Brief	�֐��Ȃǂ̒�`�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef USERUTILITY
#define	USERUTILITY

#include <iostream>
#include <cassert>
#include <cmath>

namespace UserUtility
{
	/// <summary>
	/// ���`��Ԃ���֐�
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">�����鎞�ԁi0.0����1.0�͈̔͂Ŏw��j</param>
	/// <returns>��Ԓ��̒l</returns>
	template<typename T>
	inline T Lerp(
		T a,
		T b,
		float t = 0.1f
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
	/// ���[�v�N�����v�֐�
	/// </summary>
	/// <param name="v">�Ώےl</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>�͈͓��F�Ώےl�A�����˔j�F�ő�l�A����˔j�F�ŏ��l</returns>
	template<typename T>
	inline T LoopClamp(
		T v,
		T min,
		T max
	)
	{
		if (v < min) { return max; }
		if (v > max) { return min; }

		return v;
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

	// �ߎ���v����֐�(float)
	inline bool ClosedMatch(const float& number1, const float& number2)
	{
		return (std::fabsf(number1 - number2) < FLT_EPSILON);
	}
	// �ߎ���v����֐�(SimpleMath::Vector2)
	inline bool ClosedMatch(const DirectX::SimpleMath::Vector2& number1,
		const DirectX::SimpleMath::Vector2& number2)
	{
		return DirectX::SimpleMath::Vector2::Distance(number1, number2) < 0.01f;
	}
	// �ߎ���v����֐�(SimpleMath::Vector3)
	inline bool ClosedMatch(const DirectX::SimpleMath::Vector3& number1,
		const DirectX::SimpleMath::Vector3& number2)
	{
		return DirectX::SimpleMath::Vector3::Distance(number1, number2) < 0.01f;
	}

	/// <summary>
	/// �|�C���^��null���`�F�b�N����֐�
	/// </summary>
	/// <param name="ptr">���ׂ����|�C���^</param>
	/// <returns>null�ł����True��Ԃ�</returns>
	template<typename T>
	inline bool IsNull(T* ptr)
	{
		return ptr == nullptr;
	}

	/// <summary>
	/// �|�C���^�����S�J������֐�
	/// </summary>
	/// <param name="ptr">�폜����|�C���^</param>
	/// <returns>�폜�����������ꍇ�� true�C����ȊO�� false</returns>
	template<typename T>
	inline bool DeletePtr(T* ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
			return true;
		}

		return false;
	}

	/// <summary>
	/// ���N���X�|�C���^�ɕϊ�����֐�
	/// </summary>
	/// <typeparam name="T">�ϊ���̌^</typeparam>
	/// <typeparam name="U">�ϊ����̌^</typeparam>
	/// <param name="ptr">�ϊ��Ώۂ̃|�C���^</param>
	/// <returns>���N���X�|�C���^�ɕϊ����ꂽ�|�C���^�i�ϊ��Ɏ��s�����ꍇ��nullptr�j</returns>
	template<typename T, typename U>
	inline T* UniqueCast(std::unique_ptr<U>& u)
	{
		// static_cast ���g���Ĉ��S�Ȍ^�ϊ����s��
		return static_cast<T*>(u.get());
	}
	/// <summary>
	/// std::vector�̑I�������v�f���폜����
	/// </summary>
	/// <param name="vec">�x�N�^�[�z��</param>
	/// <param name="val">�폜�������v�f</param>
	/// <returns>����</returns>
	template<typename T>
	inline void RemoveVec(std::vector<T>& vec, const T& val)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (*it == val)
			{
				it = vec.erase(it); // �C�e���[�^���X�V���č폜
				if (it == vec.end()) break; // �C�e���[�^���I�[�ɒB������I��
			}
		}
	}

	/// <summary>
	/// ���̗v�f�ɃC���N�������g����
	/// </summary>
	/// <param name="val">�v�f</param>
	/// <returns>�|�C���^�ɃC���N�������g���ꂽ�l������</returns>
	template<typename T>
	inline void Increment(T* val)
	{
		(*val) = static_cast<T>(static_cast<int>(*val) + 1);
	}
	/// <summary>
	/// ���̗v�f�Ƀf�N�������g����
	/// </summary>
	/// <param name="val">�v�f</param>
	/// <returns>�|�C���^�Ƀf�N�������g���ꂽ�l������</returns>
	template<typename T>
	inline void Decrement(T* val)
	{
		(*val) = static_cast<T>(static_cast<int>(*val) - 1);
	}

	/// <summary>
	/// �_A����_B�ւ̊p�x���v�Z����
	/// </summary>
	/// <param name="ax">�_A��X���W</param>
	/// <param name="ay">�_A��Y���W</param>
	/// <param name="bx">�_B��X���W</param>
	/// <param name="by">�_B��Y���W</param>
	/// <returns>�_A���猩���Ƃ��̓_B�̊p�x</returns>
	inline float CalcAngleAtoB(float ax, float ay, float bx, float by)
	{
		// �A�[�N�^���W�F���g���g�p���Ċp�x���v�Z���A�������ی��ɒ���
		float _angle = atan2(by - ay, bx - ax);

		// �p�x���͈�[0, 2 * ��)�Ɏ��܂�悤�ɒ���
		_angle = _angle < 0 ? _angle + static_cast<float>(2 * M_PI) : _angle;

		// �p�x�����W�A������x�ɕϊ�
		_angle *= UserUtility::Floor<float>(360.0f / (2.0f * M_PI));

		return _angle;
	}

	/// <summary>
	/// �l�����ւ���
	/// </summary>
	/// <param name="A">�l�P</param>
	/// <param name="B">�l�Q</param>
	/// <returns>�Ȃ�</returns>
	template<typename T>
	void Swap(T* A, T* B)
	{
		T _tmp = *A;
		*A = *B;
		*B = _tmp;
	}

	/// <summary>
	/// �C�[�W���O���g�p�������`�⊮�֐�
	/// </summary>
	/// <param name="a">�J�n�l</param>
	/// <param name="b">�I���l</param>
	/// <param name="t">�����鎞�ԁi0.0����1.0�͈̔͂Ŏw��j</param>
	/// <returns>��Ԓ��̒l</returns>
	template<typename T>
	inline T EasedLerp(
		T a,
		T b,
		float t
	)
	{
		float _t = (t == 0.0f) ? 0.0f : (t == 1.0f) ? 1.0f : (t < 0.5f) ?
			static_cast<float>(std::pow(2, 20 * t - 10)) / 2.0f :
			(2.0f - static_cast<float>(std::pow(2, -20 * t + 10))) / 2.0f;

		return a + _t * (b - a);
	}

	/// <summary>
	/// Vector3�̐�Βl�ϊ�
	/// </summary>
	/// <param name="v">�ϊ�������Vector3�ϐ�</param>
	/// <returns>��Βl�ϊ����Vector3</returns>
	inline DirectX::SimpleMath::Vector3 AbsVector3(DirectX::SimpleMath::Vector3 v)
	{
		return DirectX::SimpleMath::Vector3(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}

	/// <summary>
	/// �����Ƌ��̓����蔻��Ɖ����߂����s���֐�
	/// </summary>
	/// <param name="p0">�����̊J�n�n�_</param>
	/// <param name="p1">�����̏I���n�_</param>
	/// <param name="circleCenter">�I�u�W�F�N�g�̍��W</param>
	/// <param name="radius">���̔��a</param>
	/// <returns>����������TRUE</returns>
	inline bool LineSegmentCircleIntersect(
		DirectX::SimpleMath::Vector3 p0,
		DirectX::SimpleMath::Vector3 p1,
		DirectX::SimpleMath::Vector3 circleCenter,
		float radius
	)
	{
		// �����̎n�_����I�_�܂ł̃x�N�g��
		float _v1x = p1.x - p0.x;
		float _v1y = p1.y - p0.y;
		float _v1z = p1.z - p0.z;

		// �_��������̎n�_�܂ł̃x�N�g��
		float _v2x = circleCenter.x - p0.x;
		float _v2y = circleCenter.y - p0.y;
		float _v2z = circleCenter.z - p0.z;

		// �����̒����̓��
		float _squaredL1 = (_v1x * _v1x) + (_v1y * _v1y) + (_v1z * _v1z);
		// �n�_����_�܂ł̒����̓��
		float _squaredL2 = (_v2x * _v2x) + (_v2y * _v2y) + (_v2z * _v2z);

		// ����
		float _dotProduct = (_v1x * _v2x) + (_v1y * _v2y) + (_v1z * _v2z);

		if (_dotProduct == _squaredL1 * _squaredL2 && _squaredL1 >= _squaredL2)
		{
			// �����Ɠ_���d�Ȃ��Ă��邩�A�������_��蒷���ꍇ
			return true;
		}

		// �~�̒��S��������ւ̋����̓��
		float _distance =
			std::abs((_v1x * _v2y) - (_v2x * _v1y)) * std::abs((_v1x * _v2y) - (_v2x * _v1y)) / _squaredL1;

		if (_distance <= radius * radius)
		{
			// �����Ɖ~���������Ă���ꍇ
			return true;
		}

		// ����ȊO�̏ꍇ
		return false;
	}
}
#endif // USERUTILITY