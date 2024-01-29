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
//// �yMicrosoft�A�v���J���z
////  <shobjidl.h>�̎Q�l����
////
////  https://learn.microsoft.com/ja-jp/windows/win32/api/shobjidl/
////  ���y�[�W�������N�ȗ�(WindowShell)
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// �g���q�t�B���^
//==============================================================================
#define FILTER_LENGTH 2											// �t�B���^�̒���
#define EXTENSION_JSON { L"Json(Json�t�@�C��)"	, L"*.json" }	// Json�t�@�C��
#define EXTENSION_TEXT { L"�e�L�X�g �t�@�C��"	, L"*.txt" }	// Text�t�@�C��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
DiaLog::DiaLog()
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
DiaLog::~DiaLog()
{
}

//==============================================================================
// �t�@�C���p�X���擾���ĕԂ�
//==============================================================================
const wchar_t* DiaLog::GetExpFilePath()
{
	// ��O�G���[�p�ϐ�
	HRESULT _handle;

	// �_�C�A���O�p�̃C���^�[�t�F�[�X���쐬
	IFileOpenDialog* _dialog = nullptr;
	_handle = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_dialog));

	// �C���X�^���X�̍쐬�Ɏ��s�����ꍇ��nullptr��Ԃ��ďI��
	if (FAILED(_handle))
		return nullptr;

	// �g���q�t�B���^��ݒ肷��
	COMDLG_FILTERSPEC _fileTypes[] =
	{
		EXTENSION_JSON,
		EXTENSION_TEXT
	};

	// �t�B���^��ݒ�i�v�f���A�g���q�t�B���^�z��j
	_handle = _dialog->SetFileTypes(FILTER_LENGTH, _fileTypes);

	// �_�C�A���O�^�C�g����ݒ�
	_handle = _dialog->SetTitle(L"����t�@�C����I��");

	// Yes�{�^���̖��O��ݒ�
	_handle = _dialog->SetOkButtonLabel(L"����");

	// �_�C�A���O��\��
	_handle = _dialog->Show(nullptr);

	// �p�X�擾����
	wchar_t* _path = {};
	if (SUCCEEDED(_handle))
	{
		// �V�F�����쐬����
		IShellItem* _shell;
		_handle = _dialog->GetResult(&_shell);

		// �p�X���擾�o������ȉ����������s
		if (SUCCEEDED(_handle))
		{
			_handle = _shell->GetDisplayName(SIGDN_FILESYSPATH, &_path);
		}
	}

	return _path;
}
