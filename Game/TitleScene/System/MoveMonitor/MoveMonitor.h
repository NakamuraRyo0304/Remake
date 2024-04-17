/*
 *  @File   MoveMonitor.h
 *  @Brief  ��ʊĎ��ҁB
 *  @Date   2024-02-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MOVEMONITOR
#define MOVEMONITOR

class MoveMonitor
{
public:

	// �����Ԃ��擾
	bool IsMove() const { return is_moveMouse; }

	// �R���X�g���N�^
	MoveMonitor();
	// �f�X�g���N�^
	~MoveMonitor();
	// �X�V
	void Update();

private:

	// �}�E�X����ʒm
	bool is_moveMouse;
	// ����
	float m_length;

};

#endif // MOVEMONITOR