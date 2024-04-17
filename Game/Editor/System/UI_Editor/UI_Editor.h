/*
 *	@File	UI_Editor.h
 *	@Brief	�G�f�B�^UI�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_EDITOR
#define UI_EDITOR

// �e�V�[���N���X
#include "Game/Common/IUserInterface/IUserInterface.h"

class DrawKeys;
class UI_Editor final : public IUserInterface
{
public:

	// �{�^���̖��O
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

		Length_bn
	};

	// �L�[�̖��O
	enum KEY_NAME
	{
		WKEY,
		SKEY,
		AKEY,
		DKEY,

		Length__key
	};

public:

	// �{�^���̃N���b�N�󋵂��擾
	bool IsClickButton(BUTTON_NAME name) const { return is_clicks[name]; }
	// �{�^���̉��Z���W��Ԃ�
	const DirectX::SimpleMath::Vector2& GetAddPosition();

	// �R���X�g���N�^
	UI_Editor(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~UI_Editor();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:

	// �{�^���̈ʒu����
	void MoveButtonPosition();

private:

	// �{�^��
	std::vector<std::unique_ptr<Button>> m_buttons;
	// �L�[
	std::map<KEY_NAME, std::unique_ptr<DrawKeys>> m_keys;
	// �N���b�N�t���O
	bool is_clicks[BUTTON_NAME::Length_bn];
	// �{�^������ʊO�ɉB���t���O
	bool is_blindFlag;

};

#endif // UI_EDITOR