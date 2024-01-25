/*
 *	@File	ModelFactory.h
 *	@Brief	モデルを作成するファクトリークラス。
 *	@Date	2023-06-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef MODELFACTORY
#define MODELFACTORY

class ModelFactory
{
private:
	ModelFactory() = default;
	~ModelFactory() = default;

public:
	/// <summary>
	/// モデルを作成し、返却する
	/// </summary>
	/// <param name="filename">ファイルパス　拡張子は「.cmo」</param>
	/// <param name="directory">ディレクトリを設定(規定値：L"Resources/Models")</param>
	/// <returns>作成したモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateModel(const wchar_t* filename,
		const wchar_t* directory = L"Resources/Models");
};

#endif // MODELFACTORY