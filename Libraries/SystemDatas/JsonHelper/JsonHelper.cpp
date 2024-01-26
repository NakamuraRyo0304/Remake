/*
 *	@File	JsonHelper.cpp
 *	@Brief	jsonファイルのヘルパークラス。
 *	@Date	2023-01-18
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include <iostream>
#include <fstream>
#include "JsonHelper.h"

//==============================================================================
// コンストラクタ
//==============================================================================
JsonHelper::JsonHelper()
	: m_json{}
	, m_path{}
{
}

//==============================================================================
// デストラクタ
//==============================================================================
JsonHelper::~JsonHelper()
{
	m_json.clear();
	m_path.clear();
}

//==============================================================================
// 読み込み
//==============================================================================
bool JsonHelper::Load(const wchar_t* path)
{
	// Jsonファイルの読み込み
	std::ifstream _ifs(path, std::ios::in);

	if (!_ifs) return EXIT_FAILURE;

	// Jsonデータの取り出し
	_ifs >> m_json;

	// Jsonファイルを閉じる
	_ifs.close();

	// パスを保存して正常終了
	m_path = path;
	return EXIT_SUCCESS;
}

//==============================================================================
// 書き出し
//==============================================================================
bool JsonHelper::Write(std::string str)
{
	// Jsonファイルの書き込み
	std::ofstream _ofs(m_path, std::ios::out);

	if (!_ofs) return EXIT_FAILURE;

	// Jsonデータの書き出し
	_ofs << str;

	// Jsonファイルを閉じる
	_ofs.close();

	return EXIT_SUCCESS;
}
