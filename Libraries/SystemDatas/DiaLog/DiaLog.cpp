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
//// 【Microsoftアプリ開発】												////
////  <shobjidl.h>の参考文献												////
////																		////
////  https://learn.microsoft.com/ja-jp/windows/win32/api/shobjidl/			////
////  ※ページ内リンク省略(WindowShell)									    ////
////////////////////////////////////////////////////////////////////////////////

// 拡張子フィルタ
#define FILTER_LENGTH 2											// フィルタの長さ
#define EXTENSION_JSON { L"Json(Jsonファイル)"	, L"*.json" }	// Jsonファイル
#define EXTENSION_TEXT { L"テキスト ファイル"	, L"*.txt" }	// Textファイル

// コンストラクタ
DiaLog::DiaLog()
{
}

// デストラクタ
DiaLog::~DiaLog()
{
}

// ファイルパスを取得して返す
const wchar_t* DiaLog::GetExpFilePath()
{
	// 例外エラー用変数
	HRESULT hr;

	// ダイアログ用のインターフェースを作成
	IFileOpenDialog* openDialog = nullptr;
	hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&openDialog));

	// インスタンスの作成に失敗した場合はnullptrを返して終了
	if (FAILED(hr))
		return nullptr;

	// 拡張子フィルタを設定する
	COMDLG_FILTERSPEC types[] =
	{
		EXTENSION_JSON,
		EXTENSION_TEXT
	};

	// フィルタを設定（要素数、拡張子フィルタ配列）
	hr = openDialog->SetFileTypes(FILTER_LENGTH, types);

	// ダイアログタイトルを設定
	hr = openDialog->SetTitle(L"操作ファイルを選択");

	// Yesボタンの名前を設定
	hr = openDialog->SetOkButtonLabel(L"操作");

	// ダイアログを表示
	hr = openDialog->Show(nullptr);

	// パス取得処理
	wchar_t* path = {};
	if (SUCCEEDED(hr))
	{
		// シェルを作成する
		IShellItem* shell;
		hr = openDialog->GetResult(&shell);

		// パスが取得出来たら以下処理を実行
		if (SUCCEEDED(hr))
		{
			hr = shell->GetDisplayName(SIGDN_FILESYSPATH, &path);
		}
	}

	return path;
}
