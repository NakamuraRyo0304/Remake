/*
 *	@File	UI_Title.h
 *	@Brief	�^�C�g��UI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_TITLE
#define UI_TITLE

 //==============================================================================
 // �e�V�[���N���X
 //==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Title final : public IUserInterface
{
private:

	// �{�^��
	std::unique_ptr<Button> m_start;
	std::unique_ptr<Button> m_exit;

	// �N���b�N����
	bool is_startClick;
	bool is_exitClick;

private:

	// �z�o�[���̃A���t�@�l
	static const float RELEASE_ALPHA;

	// �A���t�@�l�̓��쑬�x
	static const float ALPHA_FADE_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Title(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Title();

	/// <summary>
	/// �������֐�
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

public:

	// �X�^�[�g�{�^����������
	const bool& IsClickStart() { return is_startClick; }
	// �I���{�^����������
	const bool& IsClickExit() { return is_exitClick; }
};

#endif // UI_TITLE