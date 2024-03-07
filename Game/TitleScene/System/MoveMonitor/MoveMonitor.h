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
private:

	// �}�E�X����ʒm
	bool is_moveMouse;

	// ����
	float m_length;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	MoveMonitor();
	~MoveMonitor();

	/// <summary>
	/// �X�V�֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// ����ʒm
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>��������True</returns>
	bool IsMove() const { return is_moveMouse; }
};

#endif // MOVEMONITOR