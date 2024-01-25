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
private:
	const wchar_t* DIRECTORY = L"Resources/DebugModels";

private:
	GeometricFactory() = default;
	~GeometricFactory() = default;

public:
	/// <summary>
	/// �L���[�u���쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�L���[�u�̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateCube();
	/// <summary>
	/// �V�����_�[���쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�V�����_�[�̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateCylinder();
	/// <summary>
	/// �X�t�B�A���쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�X�t�B�A�̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateSphere();
	/// <summary>
	/// �X�U���k���쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�X�U���k�̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateSusanne();
	/// <summary>
	/// �R�[�����쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�R�[���̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateCone();
	/// <summary>
	/// �t���A���쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�t���A�̃��f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateFloor();
};

#endif // GEOMETRICFACTORY