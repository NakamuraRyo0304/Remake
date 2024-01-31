/*
 *	@File	Animation2DSprite.h
 *	@Brief	2D�X�v���C�g�̃A�j���[�V�����N���X�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ANIMATION2DSPRITE
#define ANIMATION2DSPRITE

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using PrimitiveVertex = PrimitiveBatch<VertexPositionColorTexture>;

class Animation2DSprite
{
private:

	//==============================================================================
	// �V�F�[�_�[�̒�`(���_�E�s�N�Z���E�W�I���g��)
	//==============================================================================
	struct Shaders
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		VS;			// ���_�V�F�[�_�[
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		PS;			// �s�N�Z���V�F�[�_�[
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	GS;			// �W�I���g���V�F�[�_�[
	};

	//==============================================================================
	// �R���X�^���g�o�b�t�@�̒�`
	//==============================================================================
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		World;						// ���[���h�s��
		DirectX::SimpleMath::Matrix		View;						// �r���[�s��
		DirectX::SimpleMath::Matrix		Proj;						// �v���W�F�N�V�����s��
		DirectX::SimpleMath::Vector4    Move;						// �ϓ�����l
	};

	//==============================================================================
	// �^�̃T�C�Y�̒�`
	//==============================================================================
	const UINT SV3 = sizeof(DirectX::SimpleMath::Vector3);			// Vector3�̃T�C�Y
	const UINT SV4 = sizeof(DirectX::SimpleMath::Vector4);			// Vector4�̃T�C�Y
	const UINT SV7 = SV3 + SV4;										// SV3��SV4�̑��a
	const D3D11_INPUT_CLASSIFICATION V_DATA = D3D11_INPUT_PER_VERTEX_DATA;	// ���_�f�[�^

	//==============================================================================
	// �C���v�b�g���C�A�E�g�̍쐬
	//==============================================================================
	const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	V_DATA, 0 },
		{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, SV3,	V_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, SV7,	V_DATA, 0 },
	};

private:

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<PrimitiveVertex> m_batch;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �V�F�[�_�[
	std::unique_ptr<Shaders> m_shaders;

	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// �e�N�X�`���̍��W�i�O�����j
	DirectX::SimpleMath::Vector3 m_position;


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Animation2DSprite();
	~Animation2DSprite();

	/// <summary>
	/// ���\�[�X�̍쐬
	/// </summary>
	/// <param name="path">�e�N�X�`���p�X</param>
	/// <returns>�Ȃ�</returns>
	void CreateResources(const wchar_t* path);

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// �r���{�[�h���֐�
	/// </summary>
	/// <param name="eye">�J�����ʒu</param>
	/// <param name="target">�����_</param>
	/// <param name="up">�����</param>
	/// <returns>�Ȃ�</returns>
	void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up);

	// ���W��ݒ�
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_position = pos; }

private:

	/// <summary>
	/// �R���X�^���g�o�b�t�@�쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateConstBuffer();

	/// <summary>
	/// �V�F�[�_�[�̍쐬
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>���_�V�F�[�_�[�̃f�[�^</returns>
	std::vector<uint8_t> CreateShaders();

	/// <summary>
	/// �C���v�b�g���C�A�E�g�̍쐬
	/// </summary>
	/// <param name="vs">���_�V�F�[�_�[</param>
	/// <returns>�Ȃ�</returns>
	void CreateInputLayout(std::vector<uint8_t> vs);
};

#endif // ANIMATION2DSPRITE