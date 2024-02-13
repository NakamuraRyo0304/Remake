/*
 *  @File   Timer.h
 *  @Brief  �^�C�}�[�B
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

	// �^�C�}�[�̃��[�h
	enum Mode
	{
		limited,		// �����t��
		infinited,		// ����

		length,
	};

private:

	// �J�E���g/��������
	float m_count, m_limits;

	// ���s�t���O/�A���[��
	bool is_do, is_alarm;

	// ���[�h
	Mode m_mode;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mode">�^�C�}�[�̃��[�h</param>
	/// <param name="limitedSeconds">��������(�Ȃ���Εs�v)</param>
	/// <returns>�Ȃ�</returns>
	Timer(Mode mode, float limitedSeconds = std::numeric_limits<float>::max());
	~Timer();

	/// <summary>
	/// �^�C�}�[�X�^�[�g
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Start();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	/// <param name="updown">True:�J�E���g�A�b�v/Down:�J�E���g�_�E��(�f�t�H���g��True)</param>
	/// <returns>�Ȃ�</returns>
	void Update(bool updown = true);

	/// <summary>
	/// �^�C�}�[�X�g�b�v
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Stop();

	/// <summary>
	/// �^�C�}�[���Z�b�g
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Reset() { m_count = 0.0f; }

public:

	// ���~�b�g�ɒB������A���[����ʒm
	const bool& Alarm() { return is_alarm; }

	// �J�E���g���擾
	const float& GetCount() { return m_count; }
};

#endif // TIMER