/*
 *	@File	Editor.h
 *	@Brief	�G�f�B�^�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITOR
#define EDITOR

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/IScene/IScene.h"

//==============================================================================
// �I�u�W�F�N�g�X�e�[�^�X
//==============================================================================
#include "Game/Common/IGameObject/IGameObjectStates.h"

class AdminCamera;
class BlockManager;
class EditorCollision;
class UI_Editor;
class Editor final : public IScene
{
private:

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;

	// �u���b�N�}�l�[�W��
	std::unique_ptr<BlockManager> m_blockManager;

	// UI
	std::unique_ptr<UI_Editor> m_ui;

	// �G�f�B�^�R���W����
	std::unique_ptr<EditorCollision> m_editorCollision;

	// �`�悷��I�u�W�F�N�gID
	ID m_selectionID;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Editor();
	~Editor();

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

	/// <summary>
	/// �R���W�����X�V
	/// </summary>
	/// <param name="id">�ύX�������u���b�N��ID</param>
	/// <returns>�Ȃ�</returns>
	void UpdateCollisions(ID id);
};

#endif // Editor