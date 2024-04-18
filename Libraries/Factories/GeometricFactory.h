/*
 *	@File	GeometricFactory.h
 *	@Brief	�v���~�e�B�u���f�����쐬����t�@�N�g���[�B
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GEOMETRICFACTORY
#define GEOMETRICFACTORY

// ���f���t�@�N�g�����g���č쐬����
class ModelFactory;
class GeometricFactory
{
public:

	// �L���[�u���쐬
	static std::unique_ptr<DirectX::Model> CreateCube();
	// �V�����_�[���쐬
	static std::unique_ptr<DirectX::Model> CreateCylinder();
	// �X�t�B�A���쐬
	static std::unique_ptr<DirectX::Model> CreateSphere();
	// �X�U���k���쐬
	static std::unique_ptr<DirectX::Model> CreateSusanne();
	// �R�[�����쐬
	static std::unique_ptr<DirectX::Model> CreateCone();
	// �t���A���쐬
	static std::unique_ptr<DirectX::Model> CreateFloor();

private:

	// �f�B���N�g��
	const wchar_t* DIRECTORY = L"Resources/DebugModels";

private:

	// �R���X�g���N�^
	GeometricFactory() = default;
	// �f�X�g���N�^
	~GeometricFactory() = default;

};

#endif // GEOMETRICFACTORY