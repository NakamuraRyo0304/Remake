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

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	DiaLog();
	~DiaLog();

	/// <summary>
	/// ファイルパスをエクスプローラーから取得する
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>開いたファイルパス</returns>
	const wchar_t* GetExpFilePath();
};

#endif // DIALOG