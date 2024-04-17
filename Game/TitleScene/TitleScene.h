/*
 *	@File	TitleScene.h
 *	@Brief	�^�C�g���V�[���B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TITLESCENE
#define	TITLESCENE

// �e�V�[���N���X
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky_Title;
class Bird_Title;
class UI_Title;
class Water;
class Logo;
class Timer;
class Iceberg;
class Island;
class MoveMonitor;
class TitleScene final : public IScene
{
public:

	// �R���X�g���N�^
	TitleScene();
	// �f���X�g���N�^
	~TitleScene();
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

	// ���S�̃t�F�[�h�C�����x
	static const float LOGO_FADE_IN_SPEED;
	// ���S�̃t�F�[�h�A�E�g���x
	static const float LOGO_FADE_OUT_SPEED;
	// �S���̂P
	const float QUARTER = 0.25f;

private:

	// �V�[�����̕ϐ��������֐�
	void SetSceneValues() override;
	// �f�o�b�O�`��
	void DebugDraw(DirectX::CommonStates& states) override;

private:

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;
	// UI
	std::unique_ptr<UI_Title> m_ui;
	// �X�J�C��
	std::unique_ptr<Sky_Title> m_sky;
	// �g��
	std::unique_ptr<Bird_Title> m_birdTitle;
	// ��
	std::unique_ptr<Water> m_water;
	// �^�C�g�����S
	std::unique_ptr<Logo> m_logo;
	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;
	// �X�R
	std::unique_ptr<Iceberg> m_iceberg;
	// �Ǔ�
	std::unique_ptr<Island> m_island;
	// ���j�^�[�Ď���
	std::unique_ptr<MoveMonitor> m_moveMonitor;

};

#endif // TITLESCENE