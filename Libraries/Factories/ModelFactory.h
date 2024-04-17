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
public:

	// ���f�����쐬���A�ԋp����
	static std::unique_ptr<DirectX::Model> CreateModel(const wchar_t* filename,
		const wchar_t* directory = L"Resources/Models");

private:

	// �R���X�g���N�^
	ModelFactory() = default;
	// �f�X�g���N�^
	~ModelFactory() = default;
};

#endif // MODELFACTORY