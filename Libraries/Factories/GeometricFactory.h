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
private:
	const wchar_t* DIRECTORY = L"Resources/DebugModels";

private:
	GeometricFactory() = default;
	~GeometricFactory() = default;

public:
	/// <summary>
	/// キューブを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>キューブのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateCube();
	/// <summary>
	/// シリンダーを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>シリンダーのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateCylinder();
	/// <summary>
	/// スフィアを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>スフィアのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateSphere();
	/// <summary>
	/// スザンヌを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>スザンヌのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateSusanne();
	/// <summary>
	/// コーンを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>コーンのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateCone();
	/// <summary>
	/// フロアを作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>フロアのモデルデータ</returns>
	static std::unique_ptr<DirectX::Model> CreateFloor();
};

#endif // GEOMETRICFACTORY