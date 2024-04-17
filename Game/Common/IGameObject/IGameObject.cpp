/*
 *	@File	IGameObject.cpp
 *	@Brief	�Q�[���I�u�W�F�N�g�B
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "IGameObject.h"

// �R���X�g���N�^
IGameObject::IGameObject(const wchar_t* path, const wchar_t* dpath, SimpleMath::Vector3 pos)
	:
	m_world(),					// ���[���h�s��
	m_parentMatrix(),			// �e���[���h�s��
	m_position(pos),			// ���W
	m_initialPosition(pos),		// �������W
	m_scale(),					// �X�P�[��
	m_initialScale(),			// �����X�P�[��
	m_rotate(),					// ��]
	m_filePath(path),			// ���f���p�X
	m_directoryPath(dpath),		// �f�B���N�g���p�X
	m_id(ID::Default),			// �I�u�W�F�N�gID
	is_active(true)				// �A�N�e�B�u��
{
	CreateWorldMatrix();
}

// ���[���h�}�g���N�X���쐬
void IGameObject::CreateWorldMatrix()
{
	// �X�P�[����ύX
	SimpleMath::Matrix scale =
		SimpleMath::Matrix::CreateScale(GetScale());
	// ��]��ύX
	SimpleMath::Matrix rotate =
		SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// ���W��ύX
	SimpleMath::Matrix trans =
		SimpleMath::Matrix::CreateTranslation(GetPosition());

	// �ύX�����f�[�^�𔽉f
	m_world = scale * rotate * trans;
}

// ���f�����쐬����
void IGameObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

// ���f����j������
void IGameObject::ReleaseModel()
{
	m_model.reset();
}

// ���f����ύX����
void IGameObject::ChangeModel(const wchar_t* path)
{
	m_filePath = path;
	CreateModel();
}