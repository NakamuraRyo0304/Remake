/*
 *	@File	ModelFactory.cpp
 *	@Brief	���f�����쐬����t�@�N�g���[�N���X�B
 *	@Date	2023-06-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "ModelFactory.h"

// ���f���̍쐬
std::unique_ptr<Model> ModelFactory::CreateModel(const wchar_t* filename, const wchar_t* directory)
{
	auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// ���f���̍쐬(�쐬���݂̂̎g���̂�)
	std::unique_ptr<EffectFactory> fx =
		std::make_unique<EffectFactory>(device);

	// �f�B���N�g���̐ݒ�
	fx->SetDirectory(directory);

	// ���f���f�[�^�̓ǂݍ���
	std::unique_ptr<Model> model = Model::CreateFromCMO(
		device, filename, *fx);

	// �쐬�������f����ԋp
	return model;
}