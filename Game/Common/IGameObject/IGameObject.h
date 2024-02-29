/*
 *	@File	IGameObject.h
 *	@Brief	�Q�[���I�u�W�F�N�g�B
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

//==============================================================================
// �I�u�W�F�N�g�̃X�e�[�^�X
//==============================================================================
#include "IGameObjectStates.h"

class IGameObject
{
private:
	// ---���f���f�[�^---
	std::unique_ptr<DirectX::Model> m_model;

	// ---���f���p�X---
	const wchar_t* m_filePath;
	// ---�f�B���N�g���p�X---
	const wchar_t* m_directoryPath;

	// ---���[���h�s��---
	DirectX::SimpleMath::Matrix m_world;		// ���̃I�u�W�F�N�g�̃}�g���N�X
	DirectX::SimpleMath::Matrix m_parentMatrix;	// �e�̃I�u�W�F�N�g�̃}�g���N�X

private:

	// ---���W---
	DirectX::SimpleMath::Vector3 m_position;		// ���݂̍��W
	DirectX::SimpleMath::Vector3 m_initialPosition;	// �����̍��W
	// ---�X�P�[��---
	DirectX::SimpleMath::Vector3 m_scale;			// ���݂̃X�P�[��
	DirectX::SimpleMath::Vector3 m_initialScale;	// �����̃X�P�[��
	// ---��]---
	DirectX::SimpleMath::Vector3 m_rotate;

	// ---�I�u�W�F�N�gID---
	ID m_id;

	// ---�I�u�W�F�N�g�̏d��---
	double m_weight;

	// ---�A�N�e�B�u�t���O---
	bool is_active;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mpath">���f���p�X</param>
	/// <param name="dpath">�f�B���N�g���p�X</param>
	/// <param name="pos">�����ʒu</param>
	/// <returns>�Ȃ�</returns>
	IGameObject(const wchar_t* mpath, const wchar_t* dpath,
		DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	~IGameObject() = default;
	bool operator==(const IGameObject& other) const
	{
		bool _id = m_id == other.m_id;
		bool _iniPos = m_initialPosition == other.m_initialPosition;
		bool _weight = m_weight == other.m_weight;
		return _id && _iniPos && _weight;
	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Update() = 0;
	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="context">�R���e�L�X�g</param>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <param name="wireframe">���C���[�t���[��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

public:

	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition()        const { return m_position; }
	// �������W���擾
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	// �X�P�[�����擾
	DirectX::SimpleMath::Vector3 GetScale()           const { return m_scale; }
	// �����X�P�[�����擾
	DirectX::SimpleMath::Vector3 GetInitialScale()    const { return m_initialScale; }
	// ��]���擾
	DirectX::SimpleMath::Vector3 GetRotate()          const { return m_rotate; }
	// ���[���h�}�g���N�X���擾
	DirectX::SimpleMath::Matrix GetWorldMatrix()      const { return m_world; }
	// �e�̃}�g���N�X���擾
	DirectX::SimpleMath::Matrix GetParentMatrix()     const { return m_parentMatrix; }
	// ID���擾
	ID GetID()                                        const { return m_id; }
	// �d�����擾
	double GetWeight()                                const { return m_weight; }
	// �A�N�e�B�u�󋵂��擾
	bool IsActive()									  const { return is_active; }
	// ���f�����Q�Ƃ���
	std::unique_ptr<DirectX::Model>& GetModel()				{ return m_model; }

public:

	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& pos)        { m_position = pos; }
	// �������W��ݒ�
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }
	// �X�P�[����ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale)         { m_scale = scale; }
	// �����X�P�[����ݒ�
	void SetInitialScale(const DirectX::SimpleMath::Vector3& scale)  { m_initialScale = scale; }
	// ��]��ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate)       { m_rotate = rotate; }
	// �e�̃}�g���N�X��ݒ�
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix)  { m_parentMatrix = matrix; }
	// ID��ݒ�
	void SetID(const ID& id)                                         { m_id = id; }
	// �d����ݒ�
	void SetWeight(const double& weight)                             { m_weight = weight; }
	// �A�N�e�B�u�󋵂�ݒ�
	void SetActive(const bool& flag)								 { is_active = flag; }

public:
	// ���[���h�}�g���N�X���쐬
	void CreateWorldMatrix();
	// ���f�����쐬����
	void CreateModel();
	// ���f���������[�X����
	void ReleaseModel();
	// ���f����ύX����
	void ChangeModel(const wchar_t* path);
};

#endif // IGAMEOBJECT