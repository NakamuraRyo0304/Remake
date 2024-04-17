/*
 *	@File	DiaLog.cpp
 *	@Brief	�G�N�X�v���[���[�֘A�B
 *	@Date	2023-01-29
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include <shobjidl.h>
#include "DiaLog.h"

////////////////////////////////////////////////////////////////////////////////
//// �yMicrosoft�A�v���J���z												////
////  <shobjidl.h>�̎Q�l����												////
////																		////
////  https://learn.microsoft.com/ja-jp/windows/win32/api/shobjidl/			////
////  ���y�[�W�������N�ȗ�(WindowShell)									    ////
////////////////////////////////////////////////////////////////////////////////

// �g���q�t�B���^
#define FILTER_LENGTH 2											// �t�B���^�̒���
#define EXTENSION_JSON { L"Json(Json�t�@�C��)"	, L"*.json" }	// Json�t�@�C��
#define EXTENSION_TEXT { L"�e�L�X�g �t�@�C��"	, L"*.txt" }	// Text�t�@�C��

// �R���X�g���N�^
DiaLog::DiaLog()
{
}

// �f�X�g���N�^
DiaLog::~DiaLog()
{
}

// �t�@�C���p�X���擾���ĕԂ�
const wchar_t* DiaLog::GetExpFilePath()
{
	// ��O�G���[�p�ϐ�
	HRESULT hr;

	// �_�C�A���O�p�̃C���^�[�t�F�[�X���쐬
	IFileOpenDialog* openDialog = nullptr;
	hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&openDialog));

	// �C���X�^���X�̍쐬�Ɏ��s�����ꍇ��nullptr��Ԃ��ďI��
	if (FAILED(hr))
		return nullptr;

	// �g���q�t�B���^��ݒ肷��
	COMDLG_FILTERSPEC types[] =
	{
		EXTENSION_JSON,
		EXTENSION_TEXT
	};

	// �t�B���^��ݒ�i�v�f���A�g���q�t�B���^�z��j
	hr = openDialog->SetFileTypes(FILTER_LENGTH, types);

	// �_�C�A���O�^�C�g����ݒ�
	hr = openDialog->SetTitle(L"����t�@�C����I��");

	// Yes�{�^���̖��O��ݒ�
	hr = openDialog->SetOkButtonLabel(L"����");

	// �_�C�A���O��\��
	hr = openDialog->Show(nullptr);

	// �p�X�擾����
	wchar_t* path = {};
	if (SUCCEEDED(hr))
	{
		// �V�F�����쐬����
		IShellItem* shell;
		hr = openDialog->GetResult(&shell);

		// �p�X���擾�o������ȉ����������s
		if (SUCCEEDED(hr))
		{
			hr = shell->GetDisplayName(SIGDN_FILESYSPATH, &path);
		}
	}

	return path;
}
