/*
 *	@File	Input.h
 *	@Brief	�C���v�b�g�V�X�e���B
 *	@Date	2023-10-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef INPUT
#define INPUT

class Input
{
public:

	// �L�[�{�[�h�g���b�J�[���擾
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTrack();
	// �}�E�X�g���b�J�[���擾
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTrack();

	// �C���X�^���X���擾
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}
	// �f�X�g���N�^
	~Input() = default;
	// �X�V
	void Update();

private:

	// �R���X�g���N�^
	Input();

private:

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// �L�[�������ꂽ�u�Ԃ����m����
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// �}�E�X�������ꂽ�u�Ԃ����m����
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseStateTracker;

};

#endif // INPUT