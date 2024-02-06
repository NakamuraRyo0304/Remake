/*
 *  @File   ShadowMap.h
 *  @Brief  �V���h�E�}�b�v�B
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SHADOWMAP
#define SHADOWMAP

class DepthStencil;
class ShadowMap
{
private:

	// �V���h�E�}�b�v�̃T�C�Y
	static const int SHADOWMAP_SIZE = 512;

	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// �f�v�X�X�e���V��
	std::unique_ptr<DepthStencil> m_depthStencil;

	// �f�v�X���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vsDep;

	// �f�v�X�s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_psDep;

	// ���C�g�̈ʒu
	DirectX::SimpleMath::Vector3 m_lightPosition;

	// ���C�g�̉�]
	DirectX::SimpleMath::Quaternion m_lightRotate;

	// �V���h�E�}�b�v�̃R���X�^���g�o�b�t�@
	struct ShadowBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;	// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;		// ���C�g�̊���
	};

	// �V���h�E�}�b�v�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant;

	// ���C�g�e���͈͂̃R���X�^���g�o�b�t�@
	struct LightFovBuffer
	{
		float fCosTheta;		// �X�|�b�g���C�g��fov/2
		int pad[3];
	};

	// ���C�g�t�H�u�o�b�t�@�ւ̃|�C���^
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_lightConstant;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler, m_linearWrap;

	// �X�|�b�g���C�g�͈̔͂̊p�x
	float m_lightTheta;

	// �f�v�X�����_/�V���h�E�����_
	ShaderLambda m_depth, m_shadow;

	// ���C�g�̃r���[�ƃv���W�F�N�V����
	DirectX::SimpleMath::Matrix m_lightView, m_lightProj;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="states">�R�����X�e�[�g�|�C���^</param>
	/// <returns>�Ȃ�</returns>
	ShadowMap(DirectX::CommonStates* states);
	~ShadowMap();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize();

	/// <summary>
	/// �e�쐬�J�n
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Begin();

	/// <summary>
	/// �e�쐬�I��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void End();

	/// <summary>
	/// �����[�X
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Release();

public:

	// �f�v�X�����_���擾
	ShaderLambda DepthOpt() { return m_depth; }

	// �V���h�E�����_���擾
	ShaderLambda ShadowOpt() { return m_shadow; }

	// ���C�g�̃r���[
	DirectX::SimpleMath::Matrix& GetLightView() { return m_lightView; }

	// ���C�g�̃v���W�F�N�V����
	DirectX::SimpleMath::Matrix& GetLightProj() { return m_lightProj; }
};

#endif // SHADOWMAP