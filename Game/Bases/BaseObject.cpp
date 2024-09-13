/*
 *  @File   BaseObject.cpp
 *  @Brief  �I�u�W�F�N�g�̊��N���X�B
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "BaseObject.h"

// �R���X�g���N�^
BaseObject::BaseObject(const wchar_t* path, const wchar_t* dpath, SimpleMath::Vector3 pos)
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

// �f�X�g���N�^
BaseObject::~BaseObject()
{
	ReleaseModel();
}

// ���[���h�s����쐬
void BaseObject::CreateWorldMatrix()
{
	// �X�P�[����ύX
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(GetScale());
	// ��]��ύX
	SimpleMath::Matrix rotate = SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// ���W��ύX
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPosition());

	// �ύX�����f�[�^�𔽉f
	m_world = scale * rotate * trans;
}

// ���f�����쐬
void BaseObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

// ���f�������
void BaseObject::ReleaseModel()
{
	m_model.reset();
}

// ���f����ύX
void BaseObject::ChangeModel(const wchar_t* path)
{
	m_filePath = path;
	CreateModel();
}
