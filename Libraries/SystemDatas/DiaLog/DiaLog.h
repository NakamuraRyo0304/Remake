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

	// �R���X�g���N�^
	DiaLog();
	// �f�X�g���N�^
	~DiaLog();
	// �t�@�C���p�X���G�N�X�v���[���[����擾
	const wchar_t* GetExpFilePath();

};

#endif // DIALOG