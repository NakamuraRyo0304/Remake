/*
 *	@File	ModelFactory.h
 *	@Brief	���f�����쐬����t�@�N�g���[�N���X�B
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
	/// ���f�����쐬���A�ԋp����
	/// </summary>
	/// <param name="filename">�t�@�C���p�X�@�g���q�́u.cmo�v</param>
	/// <param name="directory">�f�B���N�g����ݒ�(�K��l�FL"Resources/Models")</param>
	/// <returns>�쐬�������f���f�[�^</returns>
	static std::unique_ptr<DirectX::Model> CreateModel(const wchar_t* filename,
		const wchar_t* directory = L"Resources/Models");
};

#endif // MODELFACTORY