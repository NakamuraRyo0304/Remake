/*
 *	@File	DiaLog.h
 *	@Brief	エクスプローラー関連。
 *	@Date	2023-01-29
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DIALOG
#define DIALOG

class DiaLog
{
public:

	// コンストラクタ
	DiaLog();
	// デストラクタ
	~DiaLog();
	// ファイルパスをエクスプローラーから取得
	const wchar_t* GetExpFilePath();

};

#endif // DIALOG