/*
 *	@File	PlayScene.h
 *	@Brief	�v���C�V�[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYSCENE
#define	PLAYSCENE

// �e�V�[���N���X
#include "Game/BaseScene/BaseScene.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class DepthStencil;
class FlagManager;
class ImageShot;
class Iceberg;
class Sky_Play;
class StageCollision;
class Timer;
class Player;
class UI_Play;
class WorldMouse;
class Water;
class PlayScene final : public BaseScene
{
public:

	// �Q�[���^�C�}�[���擾����
	float GetGameTimer() const { return m_gameTimer; }
	// �W�߂��R�C�������擾����
	int GetCollectedCoin() const { return m_collectedCoin; }
	// �X�e�[�W�ԍ����擾����
	int GetStageNumber() const { return m_stageNumber; }

	// �R���X�g���N�^
	PlayScene(const int& number);
	// �f�X�g���N�^
	~PlayScene();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;
	// �I��
	void Finalize() override;
	// ��ʈˑ��A�f�o�C�X�ˑ��̏�����
	void CreateWDResources() override;

private:

	// �ő�ǐՐ�
	static const int MAX_FOLLOW;
	// ���̊J�n�ʒu
	static const float FLAG_START;
	// �t���O�T�C�Y�i�J�[�\���ʒu�j
	static const float FLAG_CURSOR_RATE;

	// �V���h�E�}�b�v=============================================

	// �V���h�E�}�b�v�̃T�C�Y
	static const int SHADOWMAP_SIZE;
	// ���C�g�̈ʒu
	const DirectX::SimpleMath::Vector3 LIGHT_POSITION = { 4.5f, 10.0f, 10.0f };
	// ���C�g�̉�]
	const DirectX::SimpleMath::Quaternion LIGHT_ROTATION = { 0.80f, 0.30f, -0.20f, 0.50f };
	// �͈͂̊p�x
	static const float LIGHT_THETA;
	// �����̐F
	static const float AMBIENT_COLOR;
	// ���C�g�̍ŋߋ���
	const float LIGHT_NEAR = 0.1f;
	// ���C�g�̍ŉ�����
	const float LIGHT_FAR = 250.0f;

private:

	// �V�[�����̕ϐ�������
	void SetSceneValues() override;
	// �f�o�b�O�`��
	void DebugDraw(DirectX::CommonStates& states) override;
	// �X�e�[�W�ԍ��ɉ����ăp�X��Ԃ�
	const wchar_t* GetStagePath();

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
	// �X�R
	std::unique_ptr<Iceberg> m_iceberg, m_smallberg, m_bigberg;

	// �V���h�E�}�b�v=============================================

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
	// �o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant, m_lightConstant;
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

};

#endif // PlayScene