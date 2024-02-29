/*
 *  @File   FlagManager.h
 *  @Brief  ���Ǘ��N���X�B
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAGMANAGER
#define FLAGMANAGER

class Flag;
class FlagManager
{
private:

	// ���̕`��ʒu
	std::vector<std::unique_ptr<Flag>> m_flags;

	// �擪���W
	DirectX::SimpleMath::Vector3 m_firstPosition;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	FlagManager();
	~FlagManager();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="context">�R���e�L�X�g</param>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <param name="wireframe">���C���[�t���[��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

public:

	/// <summary>
	/// �t���O��ǉ�
	/// </summary>
	/// <param name="start">�ŏ��̈ʒu</param>
	/// <param name="dropped">�����ʒu</param>
	/// <param name="max">�ő吔</param>
	/// <returns>�Ȃ�</returns>
	void AddFlag(DirectX::SimpleMath::Vector3 start,DirectX::SimpleMath::Vector3 dropped, const int& max);

	/// <summary>
	/// �t���O���폜
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void PickFlag();

	/// <summary>
	/// �t���O�z����擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�t���O�z��</returns>
	std::vector<std::unique_ptr<Flag>>& GetFlags() { return m_flags; }

	/// <summary>
	/// ��Ԑ擪�̃t���O���L�т�������True��Ԃ�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	bool IsFirstArrived();

	/// <summary>
	/// ��Ԑ擪�̃p�X�̍��W���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	const DirectX::SimpleMath::Vector3& GetFirstPath();
};

#endif // FLAGMANAGER