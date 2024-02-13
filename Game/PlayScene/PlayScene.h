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
class ImageShot;
class Sky_Play;
class StageCollision;
class Timer;
class Player;
class UI_Play;
class WorldMouse;
class Water;
class PlayScene final : public IScene
{
private:

	// �X�e�[�W�ԍ��E�W�߂��R�C����
	int m_stageNumber, m_collectedCoin;

	// �Q�[���^�C�}�[
	float m_gameTimer;

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

	// �X�N�V��
	std::unique_ptr<ImageShot> m_imageShot;

	// ����
	std::unique_ptr<Water> m_water;

	// UI
	std::unique_ptr<UI_Play> m_ui;

	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;

	// �X�N�V���ۑ���
	std::wstring m_stageTexPath;

private:

	// �ő�ǐՐ�
	static const int MAX_FOLLOW;

	// ���̊J�n�ʒu
	static const float FLAG_START;

	// �t���O�T�C�Y�i�J�[�\���ʒu�j
	static const float FLAG_CURSOR_RATE;

private:

	// �V���h�E�}�b�v�̃T�C�Y
	static const int SHADOWMAP_SIZE;

	// ���C�g�̈ʒu/��]/�͈͂̊p�x/�����̐F
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	static const DirectX::SimpleMath::Quaternion LIGHT_ROTATION;
	static const float LIGHT_THETA;
	static const float AMBIENT_COLOR;

	// ���C�g�̃j�A�N���b�v�E�t�@�[�N���b�v
	const float LIGHT_NEAR = 0.1f;
	const float LIGHT_FAR = 250.0f;

private:

	// �����_�[�e�N�X�`��
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// �f�v�X�X�e���V��
	std::unique_ptr<DepthStencil> m_depthStencil;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vsDep, m_vs;

	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_psDep, m_ps;

	// �T���v���[
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	// �V���h�E�o�b�t�@
	struct ShadowBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
		DirectX::XMVECTOR lightPosition;	// ���C�g�̈ʒu
		DirectX::XMVECTOR lightDirection;	// ���C�g�̕���
		DirectX::XMVECTOR lightAmbient;		// ���C�g�̊���
	};

	// ���C�g�o�b�t�@
	struct LightFovBuffer
	{
		float fCosTheta;		// �X�|�b�g���C�g��fov/2
		int pad[3];
	};

	// �V���h�E/���C�g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant, m_lightConstant;


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

public:

	// �Q�[���^�C�}�[���擾����
	const float& GetGameTimer() { return m_gameTimer; }

	// �W�߂��R�C�������擾����
	const int& GetCollectedCoin() { return m_collectedCoin; }

private:

	// �X�e�[�W�ԍ��ɉ����ăp�X��Ԃ�
	const wchar_t* GetStagePath();

};

#endif // PlayScene