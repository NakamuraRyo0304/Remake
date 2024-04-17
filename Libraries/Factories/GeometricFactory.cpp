/*
 *	@File	GeometricFactory.cpp
 *	@Brief	プリミティブモデルを作成するファクトリー。
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "ModelFactory.h"
#include "GeometricFactory.h"

// キューブを作成
std::unique_ptr<Model> GeometricFactory::CreateCube()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cube.cmo",
		L"Resources/DebugModels")
	);
}

// シリンダーを作成
std::unique_ptr<Model> GeometricFactory::CreateCylinder()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cylinder.cmo",
		L"Resources/DebugModels")
	);
}

// スフィアを作成
std::unique_ptr<Model> GeometricFactory::CreateSphere()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Sphere.cmo",
		L"Resources/DebugModels")
	);
}

// スザンヌを作成
std::unique_ptr<Model> GeometricFactory::CreateSusanne()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Susanne.cmo",
		L"Resources/DebugModels")
	);
}

// コーンを作成
std::unique_ptr<Model> GeometricFactory::CreateCone()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cone.cmo",
		L"Resources/DebugModels")
	);
}

// フロアを作成
std::unique_ptr<Model> GeometricFactory::CreateFloor()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Floor.cmo",
		L"Resources/DebugModels")
	);
}

