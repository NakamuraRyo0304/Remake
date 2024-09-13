/*
 *  @File   BaseObject.h
 *  @Brief  �I�u�W�F�N�g�̊��N���X�B
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BASEOBJECT
#define BASEOBJECT

// �C���^�[�t�F�[�X
#include "Game/Interfaces/IGameObject.h"

class BaseObject : public IGameObject
{
public:

	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// �������W���擾
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	// �������W��ݒ�
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }
	// �X�P�[�����擾
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	// �X�P�[����ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	// �����X�P�[�����擾
	DirectX::SimpleMath::Vector3 GetInitialScale() const { return m_initialScale; }
	// �����X�P�[����ݒ�
	void SetInitialScale(const DirectX::SimpleMath::Vector3& scale) { m_initialScale = scale; }
	// ��]���擾
	DirectX::SimpleMath::Vector3 GetRotate() const { return m_rotate; }
	// ��]��ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }
	// ���[���h�}�g���N�X���擾
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_world; }
	// �e�̃}�g���N�X��ݒ�
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix) { m_parentMatrix = matrix; }
	// �e�̃}�g���N�X���擾
	DirectX::SimpleMath::Matrix GetParentMatrix() const { return m_parentMatrix; }
	// ID���擾
	ID GetID() const { return m_id; }
	// ID��ݒ�
	void SetID(const ID& id) { m_id = id; }
	// �A�N�e�B�u�󋵂��擾
	bool IsActive() const { return is_active; }
	// �A�N�e�B�u�󋵂�ݒ�
	void SetActive(const bool& flag) { is_active = flag; }
	// ���f�����Q�Ƃ���
	std::unique_ptr<DirectX::Model>& GetModel() { return m_model; }

	// �R���X�g���N�^
	BaseObject(const wchar_t* path, const wchar_t* dpath, DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	// �I�y���[�^�[
	bool operator==(const BaseObject& b) const
	{
		bool id = m_id == b.m_id;
		bool pos = m_initialPosition == b.m_initialPosition;
		return id && pos;
	}

	// �f�X�g���N�^
	~BaseObject();

	// ���[���h�}�g���N�X���쐬
	void CreateWorldMatrix();
	// ���f�����쐬����
	void CreateModel();
	// ���f���������[�X����
	void ReleaseModel();
	// ���f����ύX����
	void ChangeModel(const wchar_t* path);


private:

	// ���f���f�[�^
	std::unique_ptr<DirectX::Model> m_model;
	// ���f���p�X
	const wchar_t* m_filePath;
	// �f�B���N�g���p�X
	const wchar_t* m_directoryPath;
	// �I�u�W�F�N�gID
	ID m_id;
	// �A�N�e�B�u�t���O
	bool is_active;
	// �I�u�W�F�N�g�̃}�g���N�X
	DirectX::SimpleMath::Matrix m_world;
	// �e�̃I�u�W�F�N�g�̃}�g���N�X
	DirectX::SimpleMath::Matrix m_parentMatrix;
	// ���݂̍��W
	DirectX::SimpleMath::Vector3 m_position;
	// �����̍��W
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ���݂̃X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;
	// �����̃X�P�[��
	DirectX::SimpleMath::Vector3 m_initialScale;
	// ��]
	DirectX::SimpleMath::Vector3 m_rotate;

};


#endif // BASEOBJECT