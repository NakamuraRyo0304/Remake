/*
 *	@File	TitleScene.h
 *	@Brief	�^�C�g���V�[���B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TITLESCENE
#define	TITLESCENE

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class Sky;
class Logo;
class Bird_Title;
class UI_Title;
class TitleScene final : public IScene
{
private:

	// �A�h�~���J����
	std::unique_ptr<AdminCamera> m_adminCamera;

	// UI
	std::unique_ptr<UI_Title> m_ui;

	// �X�J�C��
	std::unique_ptr<Sky> m_sky;

	// ���S
	std::unique_ptr<Logo> m_logo;

	// �g��
	std::unique_ptr<Bird_Title> m_birdTitle;


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	TitleScene();
	~TitleScene();

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
};

#endif // TITLESCENE