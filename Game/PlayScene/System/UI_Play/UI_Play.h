/*
 *	@File	UI_Play.h
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAY
#define UI_PLAY

 //==============================================================================
 // �e�V�[���N���X
 //==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Play final : public IUserInterface
{
public:

	// �Z���N�g���j���[
	enum TitleSelect { Start, Exit };

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;

	// ���W
	std::map<const wchar_t*, DirectX::SimpleMath::Vector2> m_position;

	// �F
	std::map<const wchar_t*, DirectX::SimpleMath::Vector4> m_color;

	// �J�ڐ�Z���N�g
	int m_selection;

private:

	// �I��F
	static const DirectX::SimpleMath::Vector4 RED_COLOR;

	// �F�ύX���x
	static const float COLOR_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Play(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Play();

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

	// �Z���N�g�ԍ���Ԃ�
	const int& GetSelection() { return m_selection; }
};

#endif // UI_PLAY