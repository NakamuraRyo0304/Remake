/*
 *  @File   ClearScene.h
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLEARSCENE
#define CLEARSCENE

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/IScene/IScene.h"

class MomentCanv;
class ScoreBoard;
class Timer;
class UI_Clear;
class ClearScene final : public IScene
{
private:

	// ���[�����g�L�����o�X
	std::unique_ptr<MomentCanv> m_momentCanv;

	// UI
	std::unique_ptr<UI_Clear> m_ui;

	// �X�R�A�{�[�h
	std::unique_ptr<ScoreBoard> m_coinBoard, m_timeBoard;

	// �����_���J�E���g
	std::unique_ptr<Timer> m_direction;

	// �N���A����
	float m_clearTime;

	// �W�߂��R�C����/�X�e�[�W�ԍ�/�ő�X�e�[�W�ԍ�
	int m_collectedCoin, m_stageNumber, m_maxNumber;

private:

	// ���F
	static const DirectX::SimpleMath::Vector4 BLACK_COLOR;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="time">�N���A�^�C��</param>
	/// <param name="coins">�R�C����</param>
	/// <param name="stage">�X�e�[�W�ԍ�</param>
	/// <param name="max">�ő�X�e�[�W�ԍ�</param>
	/// <returns>�Ȃ�</returns>
	ClearScene(float time, int coins, int stage, int max);
	~ClearScene();

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

	// �X�e�[�W�ԍ����擾����
	const int& GetStageNumber() { return m_stageNumber; }

private:

	// �V�[���I��
	void SceneSelection();

};

#endif // CLEARSCENE