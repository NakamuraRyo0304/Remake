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

// エイリアス宣言
using Json = nlohmann::json;

class JsonHelper
{
public:

	// データの取得
	Json GetData() const { return m_json; }
	// パスの設定(主に開いたデータを他のファイルに書き出したいときに使う)
	void SetPath(const wchar_t* path) { m_path = path; }

	// コンストラクタ
	JsonHelper();
	// デストラクタ
	~JsonHelper();
	// 読み込み
	bool Load(const wchar_t* path);
	// 書き込み
	bool Write(std::string str);

private:

	// Json
	Json m_json;
	// ファイルパス
	std::wstring m_path;

};

#endif // JSONHELPER