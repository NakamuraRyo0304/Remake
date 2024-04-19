/*
 *  @File   ClearScene.h
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLEARSCENE
#define CLEARSCENE

// �e�V�[���N���X
#include "Game/Bases/BaseScene.h"

class BG_Clear;
class MomentCanv;
class ScoreBoard;
class Timer;
class UI_Clear;
class Tape;
class Seal;
class ClearScene final : public BaseScene
{
public:

	// �X�e�[�W�ԍ����擾����
	int GetStageNumber() const { return m_stageNumber; }

	// �R���X�g���N�^
	ClearScene(float time, int coins, int stage, int max);
	// �f�X�g���N�^
	~ClearScene();
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

	// �V�[�����̕ϐ�������
	void SetSceneValues() override;
	// �f�o�b�O�`��
	void DebugDraw(DirectX::CommonStates& states) override;
	// �V�[���I��
	void SceneSelection();

private:

	// ���[�����g�L�����o�X
	std::unique_ptr<MomentCanv> m_momentCanv;
	// UI
	std::unique_ptr<UI_Clear> m_ui;
	// �X�R�A�{�[�h
	std::unique_ptr<ScoreBoard> m_coinBoard, m_timeBoard;
	// �����_���J�E���g
	std::unique_ptr<Timer> m_direction;
	// �o�b�N�O���E���h
	std::unique_ptr<BG_Clear> m_backGround;
	// �e�[�v
	std::unique_ptr<Tape> m_tape[2];
	enum Sticker { Coin, Clock, Length };
	// �V�[��
	std::unique_ptr<Seal> m_seal[Sticker::Length];
	// �N���A����
	float m_clearTime;
	// �W�߂��R�C����/�X�e�[�W�ԍ�/�ő�X�e�[�W�ԍ�
	int m_collectedCoin, m_stageNumber, m_maxNumber;

};

#endif // CLEARSCENE