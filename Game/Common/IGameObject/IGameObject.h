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

	// ---���_�V�F�[�_�[---
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS;
	// ---�s�N�Z���V�F�[�_�[---
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS;
	// ---�W�I���g���V�F�[�_�[---
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GS;

	// ---���[���h�s��---
	DirectX::SimpleMath::Matrix m_world;		// ���̃I�u�W�F�N�g�̃}�g���N�X
	DirectX::SimpleMath::Matrix m_parentMatrix;	// �e�̃I�u�W�F�N�g�̃}�g���N�X

private:

	// ---���W---
	DirectX::SimpleMath::Vector3 m_position;		// ���݂̍��W
	DirectX::SimpleMath::Vector3 m_initialPosition;	// �����̍��W
	// ---�X�P�[��---
	DirectX::SimpleMath::Vector3 m_scale;
	// ---��]---
	DirectX::SimpleMath::Vector3 m_rotate;

	// ---�I�u�W�F�N�gID---
	ID m_id;

	// ---�I�u�W�F�N�g�̏d��---
	double m_weight;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mpath">���f���p�X</param>
	/// <param name="dpath">�f�B���N�g���p�X</param>
	/// <returns>�Ȃ�</returns>
	IGameObject(const wchar_t* mpath, const wchar_t* dpath);
	~IGameObject();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	virtual void Update() = 0;
	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	virtual void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) = 0;

public:
	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// ���W��ݒ� param:: pos | �w����W
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// �������W���擾
	const DirectX::SimpleMath::Vector3& GetInitialPosition() { return m_initialPosition; }
	// �������W��ݒ� param:: pos | �w����W
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }

	// �X�P�[�����擾
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	// �X�P�[����ݒ� param:: scale | �w��X�P�[��
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	// ��]���擾
	const DirectX::SimpleMath::Vector3& GetRotate() { return m_rotate; }
	// ��]��ݒ� param:: rotate | �w���]
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }

	// ���[���h�}�g���N�X���쐬
	void CreateWorldMatrix();
	// ���[���h�}�g���N�X���擾
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_world; }
	// �e�̃}�g���N�X���擾
	const DirectX::SimpleMath::Matrix& GetParentMatrix() { return m_parentMatrix; }
	// �e�̃}�g���N�X��ݒ�
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix) { m_parentMatrix = matrix; }

	// ID���擾
	const ID& GetID() { return m_id; }
	// ID��ݒ�
	void SetID(const ID& id) { m_id = id; }

	// �d�����擾
	const double& GetWeight() { return m_weight; }
	// �d����ݒ�
	void SetWeight(const double& weight) { m_weight = weight; }

	// �o�E���f�B���O�{�b�N�X���擾
	DirectX::BoundingBox GetBoundingBox() const
	{
		SimpleMath::Vector3 _min = m_position - m_scale * 0.5f;
		SimpleMath::Vector3 _max = m_position + m_scale * 0.5f;
		return DirectX::BoundingBox(_min, _max);
	}

public:
	// ���f�����쐬����
	void CreateModel();
	// ���f�����Q�Ƃ���
	std::unique_ptr<DirectX::Model>& GetModel() { return m_model; }
	// ���f���������[�X����
	void ReleaseModel();

public:
	// ���_�V�F�[�_�[���쐬����
	void CreateVSShader(const wchar_t* vsPath);
	// ���_�V�F�[�_�[���擾����
	ID3D11VertexShader* GetVSShader() { return m_VS.Get(); }
	// ���_�V�F�[�_�[��ݒ肷��
	void SetVSShader(ID3D11VertexShader* vsShader) { m_VS = vsShader; }
	// �s�N�Z���V�F�[�_�[���쐬����
	void CreatePSShader(const wchar_t* psPath);
	// �s�N�Z���V�F�[�_�[���擾����
	ID3D11PixelShader* GetPSShader() { return m_PS.Get(); }
	// �s�N�Z���V�F�[�_�[��ݒ肷��
	void SetPSShader(ID3D11PixelShader* psShader) { m_PS = psShader; }
	// �W�I���g���V�F�[�_�[���쐬����
	void CreateGSShader(const wchar_t* gsPath);
	// �W�I���g���V�F�[�_�[���擾����
	ID3D11GeometryShader* GetGSShader() { return m_GS.Get(); }
	// �W�I���g���V�F�[�_�[��ݒ肷��
	void SetGSShader(ID3D11GeometryShader* gsShader) { m_GS = gsShader; }
};

#endif // IGAMEOBJECT