/*
 *	@File	DisplayEffect.h
 *	@Brief	��ʌ��ʁB
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DISPLAYEFFECT
#define DISPLAYEFFECT

//==============================================================================
// �f�v�X�X�e���V���̃C���N���[�h
//==============================================================================
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"

class DisplayEffect
{
public:

	//==============================================================================
	// �f�B�X�v���C�G�t�F�N�g�̎��
	//==============================================================================
	enum class DisplayMode
	{
		Default,			// �ʏ�̏��
		BrownTVEffect,		// �u���E���Ǖ���ʌ���
		MonochromeEffect,	// ���m�N����ʌ���

		Length,
	};

private:

	//==============================================================================
	// �f�v�X�X�e���V���̃��[�h���`
	//==============================================================================
	const int USER_DEPTH_MODE = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL;

	//==============================================================================
	// �X�e���V���ƃ����_�[�^�[�Q�b�g�̍\����
	//==============================================================================
	struct ViewPointer
	{
		ID3D11DepthStencilView* pDepthStencil;
		ID3D11RenderTargetView* pRenderTarget;
	};

	//==============================================================================
	// ���_���̃G�C���A�X�錾
	//==============================================================================
	using PrimitiveVertex = PrimitiveBatch<VertexPositionColorTexture>;

	//==============================================================================
	// �V�F�[�_�[�p�b�N�̒�`
	//==============================================================================
	struct ShaderPack
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
		DirectX::SimpleMath::Vector4	Time;						// �^�C�}�[
		DirectX::SimpleMath::Matrix		World;						// ���[���h�s��
		DirectX::SimpleMath::Matrix		View;						// �r���[�s��
		DirectX::SimpleMath::Matrix		Proj;						// �v���W�F�N�V�����s��
	};

	//==============================================================================
	// �^�̃T�C�Y�̒�`
	//==============================================================================
	const UINT sizeVec3 = sizeof(SimpleMath::Vector3);				// Vector3�̃T�C�Y
	const UINT sizeVec4 = sizeof(SimpleMath::Vector4);				// Vector4�̃T�C�Y

	//==============================================================================
	// �C���v�b�g���C�A�E�g�̍쐬
	//==============================================================================
	const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,					D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeVec3,			D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, sizeVec3 + sizeVec4,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//==============================================================================
	// �o�[�e�b�N�X�J�E���g
	//==============================================================================
	static const UINT VERTEX_COUNT;

private:

	// �f�B�X�v���C���[�h
	DisplayMode m_mode;

	// ��ʃT�C�Y
	RECT m_size;

	// ���[���h���W�E�g�嗦�E��]��
	DirectX::SimpleMath::Vector3 m_worldPosition, m_scale, m_rotate;

	// �V�F�[�_�[�p�b�N
	std::unique_ptr<ShaderPack> m_shaders;

	// �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V��
	std::unique_ptr<ViewPointer> m_viewPointer;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<PrimitiveVertex> m_batch;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// �V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResouce;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="rect">��ʃT�C�Y</param>
	/// <returns>�Ȃ�</returns>
	DisplayEffect(RECT rect);
	~DisplayEffect();

	/// <summary>
	/// ��ʌ��ʂ�ݒ肷��
	/// </summary>
	/// <param name="mode">��ʌ��ʂ̎��</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(const DisplayMode& mode);

	/// <summary>
	/// ��ʌ��ʊJ�n
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Begin();
	/// <summary>
	/// ��ʌ��ʏI��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void End();

	/// <summary>
	/// Start-End�ɋ��܂ꂽ�I�u�W�F�N�g�Ɍ��ʂ�K�p����
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <param name="flag">True�Ń��[���h�s��ɕϊ�</param>
	/// <returns>�Ȃ�</returns>
	void Apply(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj, const bool& flag = false);

	// ��ʌ��ʂ�ݒ�
	void SetDisplayMode(const DisplayMode& mode);
	DisplayMode const GetDisplayMode() { return m_mode; }
	// ��ʃT�C�Y��ݒ�
	void SetDisplaySize(const RECT& rect) { m_size = rect; }
	// ���W��ݒ�
	void SetWorldPosition(const DirectX::SimpleMath::Vector3& pos) { m_worldPosition = pos; }
	// �X�P�[����ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One) { m_scale = scale; }
	// ��]�ʂ�ݒ�
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate = DirectX::SimpleMath::Vector3::Zero)
	{
		m_rotate = DirectX::SimpleMath::Vector3(
			XMConvertToRadians(rotate.x),
			XMConvertToRadians(rotate.y),
			XMConvertToRadians(rotate.z)
		);
	}

private:
	/// <summary>
	/// �V�F�[�_�[���쐬����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateShaders();

	/// <summary>
	/// �V�F�[�_�[�ǂݍ���
	/// </summary>
	/// <param name="path">�t�@�C���p�X</param>
	/// <returns>�Ȃ�</returns>
	std::vector<uint8_t> ReadShader(const wchar_t* path);
};

#endif // DISPLAYEFFECT