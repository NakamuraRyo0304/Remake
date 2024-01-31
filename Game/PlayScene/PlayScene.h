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
class Sky_Play;
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
};

#endif // PlayScene