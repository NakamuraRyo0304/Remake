/*
 *	@File	UI_Editor.h
 *	@Brief	�G�f�B�^UI�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_EDITOR
#define UI_EDITOR

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Editor final : public IUserInterface
{
public:

	enum BUTTON_NAME
	{
		LoadFile,
		WriteFile,
		Flozen_bn,
		Cloud_bn,
		Coin_bn,
		Air_bn,
		Player_bn,
		Goal_bn,
		OC1_bn,
		OC2_bn,
		Spike_bn,
		Lift_bn,

		Length
	};


private:

	// �t���O
	bool is_clicks[BUTTON_NAME::Length];

	// �{�^��
	std::vector<std::unique_ptr<Button>> m_buttons;

	// �{�^������ʊO�ɉB���t���O
	bool is_blindFlag;


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Editor(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Editor();

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

	// �{�^���̃N���b�N�󋵂��擾
	const bool& IsClickButton(BUTTON_NAME name) { return is_clicks[name]; }

	// �{�^���̉��Z���W��Ԃ�
	const DirectX::SimpleMath::Vector2& GetAddPosition();

private:

	// �{�^���̈ʒu����
	void MoveButtonPosition();

};

#endif // UI_EDITOR