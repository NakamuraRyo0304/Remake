/*
 *	@File	Editor.h
 *	@Brief	�G�f�B�^�B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITOR
#define EDITOR

// �e�V�[���N���X
#include "Game/Bases/BaseScene.h"

// �I�u�W�F�N�g�X�e�[�^�X
#include "Game/Interfaces/StatesList.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class EditorCollision;
class EditorGrids;
class UI_Editor;
class WorldMouse;
class Editor final : public BaseScene
{
public:

	// �R���X�g���N�^
	Editor();
	// �f�X�g���N�^
	~Editor();
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
	// �I�u�W�F�N�g���Z�b�g����
	void SetDrawObject();
	// �R���W�����X�V
	void UpdateCollisions(ID id);

private:

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;
	// �u���b�N�}�l�[�W��
	std::unique_ptr<BlockManager> m_blockManager;
	// UI
	std::unique_ptr<UI_Editor> m_ui;
	// �G�f�B�^�R���W����
	std::unique_ptr<EditorCollision> m_editorCollision;
	// ���[���h�}�E�X
	std::unique_ptr<WorldMouse> m_worldMouse;
	// �J�[�\���I�u�W�F�N�g
	std::unique_ptr<CursorObject> m_cursorObject;
	// �G�f�B�^�p�O���b�h
	std::unique_ptr<EditorGrids> m_editorGrids;
	// �`�悷��I�u�W�F�N�gID
	ID m_selectionID;

};

#endif // Editor