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
public:

	// モデルを作成し、返却する
	static std::unique_ptr<DirectX::Model> CreateModel(const wchar_t* filename,
		const wchar_t* directory = L"Resources/Models");

private:

	// コンストラクタ
	ModelFactory() = default;
	// デストラクタ
	~ModelFactory() = default;
};

#endif // MODELFACTORY