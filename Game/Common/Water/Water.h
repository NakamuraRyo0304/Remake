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
public:

	// �R���X�g���N�^
	Water();
	// �f�X�g���N�^
	~Water();
	// ����
	void Create(const wchar_t* path);
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// �C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
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
	static const float SCALE;
	// ���_��
	static const UINT VERTEX_NUM;

private:

	// �摜�ǂݍ���
	void LoadTexture(const wchar_t* path);
	// �V�F�[�_�[�쐬
	void CreateShader();

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

	// �V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;		// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;	// �W�I���g���V�F�[�_�[
	// �s��
	DirectX::SimpleMath::Matrix m_world;				// ���[���h�s��
	DirectX::SimpleMath::Matrix m_view;					// �r���[�s��
	DirectX::SimpleMath::Matrix m_proj;					// �v���W�F�N�V�����s��

};

#endif // WATER