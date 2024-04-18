/*
 *	@File	SelectScene.h
 *	@Brief	�Z���N�g�V�[���B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SELECTSCENE
#define SELECTSCENE

// �e�V�[���N���X
#include "Game/BaseScene/BaseScene.h"

class AdminCamera;
class BlockManager;
class UI_Select;
class Water;
class BG_Select;
class SelectScene final : public BaseScene
{
public:

	// �X�e�[�W�ԍ����擾
	int GetSelectedNumber() const { return m_stageSelection; }
	// �ő�X�e�[�W�ԍ����擾
	int GetMaxNumber() const { return MAX_SAMPLE_NUM; }

	// �R���X�g���N�^
	SelectScene(const int& selection);
	// �f�X�g���N�^
	~SelectScene();
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
	// �J�����̐؂�ւ�����
	void ChangeAdminCamera();
	// �V�[���I��
	void SelectNext();

private:

	// �T���v���X�e�[�W�ԍ�
	static const int MAX_SAMPLE_NUM = 4;
	// �O�Ԃ̓G�f�B�^�̔ԍ�
	const int EDITOR_NUM = 0;

private:

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;
	// UI
	std::unique_ptr<UI_Select> m_ui;
	// �u���b�N�}�l�[�W��
	std::unique_ptr<BlockManager> m_stage[MAX_SAMPLE_NUM];
	// ��
	std::unique_ptr<Water> m_water;
	// �w�i
	std::unique_ptr<BG_Select> m_backGround;
	// �Z���N�g�ԍ�
	int m_stageSelection;

};

#endif // SELECTSCENE