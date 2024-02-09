/*
 *  @File   Water.h
 *  @Brief  ���ʁB
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef WATER
#define WATER

class Water
{
private:

	// �R���X�^���g�o�b�t�@
	struct ConstantBuffer
	{
		DirectX::SimpleMath::Matrix		World;
		DirectX::SimpleMath::Matrix		View;
		DirectX::SimpleMath::Matrix		Proj;
		float Time;
		float pad[3];
	};

	// �X�V�����Ȃ��R���X�^���g�o�b�t�@
	struct WaterConstant
	{
		float Scale;
		float pad[3];
	};

	// �摜�̃X�P�[��
	static const float WATER_SCALE;

	// ���_��
	static const UINT VERTEX_NUM;

private:

	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer, m_waterConstantBuffer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitive;

	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �e�N�X�`���n���h��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;

	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;

	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;

	// �s��
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

private:

	// �C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Water();
	~Water();

	/// <summary>
	/// �����֐�
	/// </summary>
	/// <param name="path">�摜�p�X</param>
	/// <returns>�Ȃ�</returns>
	void Create(const wchar_t* path);

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	/// <summary>
	/// �摜�ǂݍ���
	/// </summary>
	/// <param name="path">�摜�p�X</param>
	/// <returns>�Ȃ�</returns>
	void LoadTexture(const wchar_t* path);

	/// <summary>
	/// �V�F�[�_�[�쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateShader();
};

#endif // WATER