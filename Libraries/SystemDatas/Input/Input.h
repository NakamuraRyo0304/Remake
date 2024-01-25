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
private:
	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>							m_keyboard;
	// �}�E�X
	std::unique_ptr<DirectX::Mouse>								m_mouse;
	// �����ꂽ�u�Ԃ����m����
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardStateTracker;
	// �����ꂽ�u�Ԃ����m����
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseStateTracker;

private:

	// �V���O���g��
	Input();

public:

	/// <summary>
	/// �C���v�b�g���Q��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�C���v�b�g�V���O���g��</returns>
	static Input* GetInstance()
	{
		static Input in;

		return &in;
	}

	~Input() = default;

	/// <summary>
	/// �C���v�b�g�V�X�e���̍X�V
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �L�[�{�[�h�g���b�J�[���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�L�[�{�[�h�g���b�J�[</returns>
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTrack();

	/// <summary>
	/// �}�E�X�g���b�J�[���擾
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�}�E�X�g���b�J�[</returns>
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTrack();
};

#endif // INPUT