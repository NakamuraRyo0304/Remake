/*
 *	@File	GeometricFactory.h
 *	@Brief	プリミティブモデルを作成するファクトリー。
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GEOMETRICFACTORY
#define GEOMETRICFACTORY

// モデルファクトリを使って作成する
class ModelFactory;
class GeometricFactory
{
public:

	// キューブを作成
	static std::unique_ptr<DirectX::Model> CreateCube();
	// シリンダーを作成
	static std::unique_ptr<DirectX::Model> CreateCylinder();
	// スフィアを作成
	static std::unique_ptr<DirectX::Model> CreateSphere();
	// スザンヌを作成
	static std::unique_ptr<DirectX::Model> CreateSusanne();
	// コーンを作成
	static std::unique_ptr<DirectX::Model> CreateCone();
	// フロアを作成
	static std::unique_ptr<DirectX::Model> CreateFloor();

private:

	// ディレクトリ
	const wchar_t* DIRECTORY = L"Resources/DebugModels";

private:

	// コンストラクタ
	GeometricFactory() = default;
	// デストラクタ
	~GeometricFactory() = default;

};

#endif // GEOMETRICFACTORY