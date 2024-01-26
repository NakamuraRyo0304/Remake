/*
 *	@File	JsonHelper.h
 *	@Brief	jsonファイルのヘルパークラス。
 *	@Date	2023-01-18
 *  @Author NakamuraRyo
 */

// jsonライブラリのインクルード
#include "json.hpp"
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
////   Json for Modern C++                                   ////
////   Version 3.11.2                                        ////
////   Author Niels Lohmann                                  ////
////   DownLoad for URL : https://github.com/nlohmann/json   ////
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

#pragma once
#ifndef JSONHELPER
#define JSONHELPER

//==============================================================================
// エイリアス宣言
//==============================================================================
using Json = nlohmann::json;

class JsonHelper
{
private:

	// Json
	Json m_json;

	// ファイルパス
	std::wstring m_path;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	JsonHelper();
	~JsonHelper();

	/// <summary>
	/// 読み込み
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>成功判定</returns>
	bool Load(const wchar_t* path);

	/// <summary>
	/// 書き込み
	/// </summary>
	/// <param name="data">Jsonデータを変換した文字列</param>
	/// <returns>なし</returns>
	bool Write(std::string str);

	/// <summary>
	/// データの取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>解析済みデータ</returns>
	Json GetData() { return m_json; }

	/// <summary>
	/// パスの設定(主に開いたデータを他のファイルに書き出したいときに使う)
	/// </summary>
	/// <param name="path">書き出しパス</param>
	/// <returns>なし</returns>
	void SetPath(const wchar_t* path) { m_path = path; }
};

#endif // JSONHELPER