/*
 *	@File	DiaLog.h
 *	@Brief	�G�N�X�v���[���[�֘A�B
 *	@Date	2023-01-29
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DIALOG
#define DIALOG

class DiaLog
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	DiaLog();
	~DiaLog();

	/// <summary>
	/// �t�@�C���p�X���G�N�X�v���[���[����擾����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�J�����t�@�C���p�X</returns>
	const wchar_t* GetExpFilePath();
};

#endif // DIALOG