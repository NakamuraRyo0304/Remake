/*
 *  @File   Timer.h
 *  @Brief  �^�C�}�[�B
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TIMER
#define TIMER

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

public:

	// �A���[���󋵂��擾
	bool Alarm() const { return is_alarm; }
	// �J�E���g���擾
	float GetCount() const { return m_count; }

	// �R���X�g���N�^
	Timer(Mode mode, float limitedSeconds = 0.0f);
	// �f�X�g���N�^
	~Timer();
	// �^�C�}�[�X�^�[�g
	void Start();
	// �X�V
	void Update(bool updown = true);
	// �^�C�}�[�X�g�b�v
	void Stop();
	// �^�C�}�[���Z�b�g
	void Reset() { m_count = 0.0f; }
	// �ăX�^�[�g
	void ReStart();

private:

	// �J�E���g/��������
	float m_count, m_limits;
	// ���s�t���O/�A���[��
	bool is_do, is_alarm;
	// ���[�h
	Mode m_mode;

};

#endif // TIMER