/*
 *	@File	UI_Title.h
 *	@Brief	�^�C�g��UI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_TITLE
#define UI_TITLE

 // �e�V�[���N���X
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Title final : public IUserInterface
{
public:

	// �Z���N�g�ԍ���Ԃ�
	int GetSelection() const { return m_selection; }

	// ��������m�󋵂�Ԃ�
	bool IsAnything() const { return is_anything; }

	// �R���X�g���N�^
	UI_Title(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~UI_Title();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

public:

	// �Z���N�g���j���[
	enum TitleSelect { Start, Exit };

private:

	// �F�ύX���x
	static const float COLOR_SPEED;

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;
	// ���W
	std::map<const wchar_t*, DirectX::SimpleMath::Vector2> m_position;
	// �F
	std::map<const wchar_t*, DirectX::SimpleMath::Vector4> m_color;
	// �J�ڐ�Z���N�g
	int m_selection;
	// ���쌟�m�t���O
	bool is_anything;

};

#endif // UI_TITLE