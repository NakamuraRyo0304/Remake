/*
 *	@File	SelectScene.h
 *	@Brief	�Z���N�g�V�[���B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SELECTSCENE
#define SELECTSCENE

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class BlockManager;
class UI_Select;
class Water;
class BG_Select;
class SelectScene final : public IScene
{
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


public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="selection">�I���X�e�[�W</param>
	/// <returns>�Ȃ�</returns>
	SelectScene(const int& selection);
	~SelectScene();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Initialize()                             override;
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update()                                 override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw()                                   override;
	/// <summary>
	/// �I������
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Finalize()                               override;
	/// <summary>
	/// ��ʈˑ��A�f�o�C�X�ˑ��̏�����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void CreateWDResources()                      override;

private:

	/// <summary>
	/// �V�[�����̕ϐ��������֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void SetSceneValues()                         override;
	/// <summary>
	/// �f�o�b�O�`��
	/// </summary>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <returns>�Ȃ�</returns>
	void DebugDraw(DirectX::CommonStates& states) override;

public:

	// �X�e�[�W�ԍ����擾
	const int& GetSelectedNumber() { return m_stageSelection; }

	// �ő�X�e�[�W�ԍ����擾
	const int& GetMaxNumber() { return MAX_SAMPLE_NUM; }

private:

	/// <summary>
	/// �J�����̐؂�ւ�����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void ChangeAdminCamera();

	/// <summary>
	/// �V�[���I��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void SelectNext();
};

#endif // SELECTSCENE