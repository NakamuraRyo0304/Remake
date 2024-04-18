/*
 *  @File   Timer.cpp
 *  @Brief  �^�C�}�[�B
 *  @Date   2024-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Timer.h"

// �R���X�g���N�^
Timer::Timer(Mode mode, float limitedSeconds)
	:
	m_count(0.0f),				// �J�E���g
	m_mode(mode),				// ���[�h
	m_limits(limitedSeconds),	// ��������
	is_do(false),				// ���s�t���O
	is_alarm(false)				// �A���[��
{
}

// �f�X�g���N�^
Timer::~Timer()
{
}

// �^�C�}�[�X�^�[�g
void Timer::Start()
{
	is_alarm = false;
	is_do = true;
}

// �X�V
void Timer::Update(bool updown)
{
	// ���s���I�t�ŃX�L�b�v
	if (is_do == false) return;

	// �A���[�����Ȃ��Ă��Ȃ���Α�����
	{
		// �J�E���g�A�b�v
		if (updown == true && is_alarm == false)
		{
			m_count += static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());
		}

		// �J�E���g�_�E��
		if (updown == false && is_alarm == false)
		{
			m_count -= static_cast<float>(DX::StepTimer::GetInstance().GetElapsedSeconds());
		}
	}

	// ���Ԑ���������Ȃ���s����
	if (m_mode == Mode::limited)
	{
		if (std::fabsf(m_count - m_limits) < 0.01f)
		{
			is_alarm = true;
			is_do = false;
		}
	}
}

// �^�C�}�[�X�g�b�v
void Timer::Stop()
{
	is_do = false;
}

// �ăX�^�[�g
void Timer::ReStart()
{
	Stop();
	Reset();
	Start();
}
