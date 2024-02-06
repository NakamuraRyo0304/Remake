/*
 *	@File	PlayScene.h
 *	@Brief	�v���C�V�[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYSCENE
#define	PLAYSCENE

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class DepthStencil;
class FlagManager;
class Sky_Play;
class StageCollision;
class Player;
class WorldMouse;
class PlayScene final : public IScene
{
private:

	// �X�e�[�W�ԍ�
	int m_stageNumber;

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;

	// �X�J�C��
	std::unique_ptr<Sky_Play> m_sky;

	// �v���C���[
	std::unique_ptr<Player> m_player;

	// ���[���h�}�E�X
	std::unique_ptr<WorldMouse> m_worldMouse;

	// �u���b�N�}�l�[�W��
	std::unique_ptr<BlockManager> m_blockManager;

	// �X�e�[�W�̓����蔻��
	std::unique_ptr<StageCollision> m_stageCollision;

	// �J�[�\���I�u�W�F�N�g
	std::unique_ptr<CursorObject> m_cursorObject;

	// �t���O�}�l�[�W��
	std::unique_ptr<FlagManager> m_flagManager;

private:

	// �ő�ǐՐ�
	static const int MAX_FOLLOW;

	// ���̊J�n�ʒu
	static const float FLAG_START;

private:

	// �V���h�E�}�b�v�̃T�C�Y
	static const int SHADOWMAP_SIZE;

	// �A���r�G���g���C�g�̐F
	static const float AMBIENT_COLOR;

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
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	// �X�|�b�g���C�g�͈̔͂̊p�x
	float m_lightTheta;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="number">�X�e�[�W�ԍ�</param>
	/// <returns>�Ȃ�</returns>
	PlayScene(const int& number);
	~PlayScene();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize() override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw() override;
	/// <summary>
	/// �I������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Finalize() override;
	/// <summary>
	/// ��ʈˑ��A�f�o�C�X�ˑ��̏�����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateWDResources() override;

private:

	/// <summary>
	/// �V�[�����̕ϐ��������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void SetSceneValues() override;
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <returns>�Ȃ�</returns>
	void DebugDraw(DirectX::CommonStates& states) override;

private:

	// �X�e�[�W�ԍ��ɉ����ăp�X��Ԃ�
	const wchar_t* GetStagePath();

};

#endif // PlayScene