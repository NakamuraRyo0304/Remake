/*
 *	@File	GeometricFactory.cpp
 *	@Brief	�v���~�e�B�u���f�����쐬����t�@�N�g���[�B
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "ModelFactory.h"
#include "GeometricFactory.h"

// �L���[�u���쐬
std::unique_ptr<Model> GeometricFactory::CreateCube()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cube.cmo",
		L"Resources/DebugModels")
	);
}

// �V�����_�[���쐬
std::unique_ptr<Model> GeometricFactory::CreateCylinder()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cylinder.cmo",
		L"Resources/DebugModels")
	);
}

// �X�t�B�A���쐬
std::unique_ptr<Model> GeometricFactory::CreateSphere()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Sphere.cmo",
		L"Resources/DebugModels")
	);
}

// �X�U���k���쐬
std::unique_ptr<Model> GeometricFactory::CreateSusanne()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Susanne.cmo",
		L"Resources/DebugModels")
	);
}

// �R�[�����쐬
std::unique_ptr<Model> GeometricFactory::CreateCone()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Cone.cmo",
		L"Resources/DebugModels")
	);
}

// �t���A���쐬
std::unique_ptr<Model> GeometricFactory::CreateFloor()
{
	return std::move(ModelFactory::CreateModel(
		L"Resources/DebugModels/Floor.cmo",
		L"Resources/DebugModels")
	);
}

