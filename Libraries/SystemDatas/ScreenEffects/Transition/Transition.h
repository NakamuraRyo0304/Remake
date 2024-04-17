/*
 *	@File	Transition.h
 *	@Brief	��ʐ؂�ւ��̃g�����W�V�����B
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TRANSITION
#define TRANSITION

class Transition
{
public:

	// �R���X�^���g�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		World;
		DirectX::SimpleMath::Matrix		View;
		DirectX::SimpleMath::Matrix		Proj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

	// �C���v�b�g���C�A�E�g�̐ݒ�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

public:

	// �F���擾
	DirectX::XMVECTORF32 GetColor() const { return m_color; }
	// �F��ݒ�(�f�t�H���g�ō�)
	void SetColor(const DirectX::XMVECTORF32& color = DirectX::Colors::Black) { m_color = color; }

	// �R���X�g���N�^
	Transition();
	// �f�X�g���N�^
	~Transition();
	// ���\�[�X�̍쐬
	void Create(const wchar_t* path);
	// �`��
	void Draw(const float& timer);

private:

	// �摜�ǂݍ���
	void LoadTexture(const wchar_t* path);
	// �V�F�[�_�[�̍쐬
	void CreateShader();
	// �R���X�^���g�o�b�t�@�쐬
	void CreateConstBuffer();

private:

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// ���_
	DirectX::VertexPositionColorTexture m_vertice;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �t�F�[�h�F
	DirectX::XMVECTORF32 m_color;

	// �o�[�e�b�N�X�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_verShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geoShader;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBuffer;

};

#endif // TRANSITION