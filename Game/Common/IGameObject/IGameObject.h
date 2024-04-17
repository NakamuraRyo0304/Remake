/*
 *	@File	IGameObject.h
 *	@Brief	�Q�[���I�u�W�F�N�g�B
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

// �I�u�W�F�N�g�̃X�e�[�^�X
#include "IGameObjectStates.h"

class IGameObject
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

	// ���[���h�}�g���N�X���쐬
	void CreateWorldMatrix();
	// ���f�����쐬����
	void CreateModel();
	// ���f���������[�X����
	void ReleaseModel();
	// ���f����ύX����
	void ChangeModel(const wchar_t* path);

	// �R���X�g���N�^
	IGameObject(const wchar_t* mpath, const wchar_t* dpath,
		DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	// �I�y���[�^�[
	bool operator==(const IGameObject& data) const
	{
		bool id = m_id == data.m_id;
		bool iniPos = m_initialPosition == data.m_initialPosition;
		return id && iniPos;
	}
	// �f�X�g���N�^
	virtual ~IGameObject() = default;
	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

private:

	// ���f���f�[�^
	std::unique_ptr<DirectX::Model> m_model;
	// ���f���p�X
	const wchar_t* m_filePath;
	// �f�B���N�g���p�X
	const wchar_t* m_directoryPath;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;		// ���̃I�u�W�F�N�g�̃}�g���N�X
	DirectX::SimpleMath::Matrix m_parentMatrix;	// �e�̃I�u�W�F�N�g�̃}�g���N�X

	// ���W
	DirectX::SimpleMath::Vector3 m_position;		// ���݂̍��W
	DirectX::SimpleMath::Vector3 m_initialPosition;	// �����̍��W
	// �X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;			// ���݂̃X�P�[��
	DirectX::SimpleMath::Vector3 m_initialScale;	// �����̃X�P�[��
	// ��]
	DirectX::SimpleMath::Vector3 m_rotate;

	// �I�u�W�F�N�gID
	ID m_id;

	// �A�N�e�B�u�t���O
	bool is_active;

};

#endif // IGAMEOBJECT