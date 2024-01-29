/*
 *	@File	DiaLog.cpp
 *	@Brief	エクスプローラー関連。
 *	@Date	2023-01-29
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include <shobjidl.h>
#include "DiaLog.h"

////////////////////////////////////////////////////////////////////////////////
//// 【Microsoftアプリ開発】
////  <shobjidl.h>の参考文献
////
////  https://learn.microsoft.com/ja-jp/windows/win32/api/shobjidl/
////  ※ページ内リンク省略(WindowShell)
////////////////////////////////////////////////////////////////////////////////

//==============================================================================
// 拡張子フィルタ
//==============================================================================
#define FILTER_LENGTH 2											// フィルタの長さ
#define EXTENSION_JSON { L"Json(Jsonファイル)"	, L"*.json" }	// Jsonファイル
#define EXTENSION_TEXT { L"テキスト ファイル"	, L"*.txt" }	// Textファイル

//==============================================================================
// コンストラクタ
//==============================================================================
DiaLog::DiaLog()
{
}

//==============================================================================
// デストラクタ
//==============================================================================
DiaLog::~DiaLog()
{
}

//==============================================================================
// ファイルパスを取得して返す
//==============================================================================
const wchar_t* DiaLog::GetExpFilePath()
{
	// 例外エラー用変数
	HRESULT _handle;

	// ダイアログ用のインターフェースを作成
	IFileOpenDialog* _dialog = nullptr;
	_handle = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_dialog));

	// インスタンスの作成に失敗した場合はnullptrを返して終了
	if (FAILED(_handle))
		return nullptr;

	// 拡張子フィルタを設定する
	COMDLG_FILTERSPEC _fileTypes[] =
	{
		EXTENSION_JSON,
		EXTENSION_TEXT
	};

	// フィルタを設定（要素数、拡張子フィルタ配列）
	_handle = _dialog->SetFileTypes(FILTER_LENGTH, _fileTypes);

	// ダイアログタイトルを設定
	_handle = _dialog->SetTitle(L"操作ファイルを選択");

	// Yesボタンの名前を設定
	_handle = _dialog->SetOkButtonLabel(L"操作");

	// ダイアログを表示
	_handle = _dialog->Show(nullptr);

	// パス取得処理
	wchar_t* _path = {};
	if (SUCCEEDED(_handle))
	{
		// シェルを作成する
		IShellItem* _shell;
		_handle = _dialog->GetResult(&_shell);

		// パスが取得出来たら以下処理を実行
		if (SUCCEEDED(_handle))
		{
			_handle = _shell->GetDisplayName(SIGDN_FILESYSPATH, &_path);
		}
	}

	return _path;
}
