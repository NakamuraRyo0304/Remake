/*
 *	@File	UI_Select.h
 *	@Brief	�Z���N�gUI�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_SELECT
#define UI_SELECT

// �e�V�[���N���X
#include "Game/Bases/BaseUI.h"

class UI_Select final : public BaseUI
{
public:

	// �I�𒆂̃X�e�[�W�ԍ���ݒ�
	void SetSelectionNum(const int& num) { m_selection = num; }

	// �R���X�g���N�^
	UI_Select(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~UI_Select();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:

	// �F�ύX���x
	static const float COLOR_SPEED;
	// �X�e�[�W�ԍ��̊Ԋu
	static const float STAGE_TEX_SPAN;
	// �摜�̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_TEX_POS;
	// �摜�̊g�嗦
	static const float STAGE_TEX_RATE;
	// �G�f�B�^�����؂���ʒu
	const RECT_U RECT_EDIT = RECT_U(0, 0, 768, 128);
	// �X�e�[�W�����؂���ʒu
	const RECT_U RECT_GAME = RECT_U(0, 0, 382, 128);

private:

	// �F���Z�b�g�֐�
	void ResetColors();

	//

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;
	// ���W
	std::map<std::wstring, DirectX::SimpleMath::Vector2> m_position;
	// �F
	std::map<std::wstring, DirectX::SimpleMath::Vector4> m_color;
	// �I���X�e�[�W�ԍ�
	int m_selection;
	// �X�e�[�W�摜�A���t�@�l
	float m_stageAlpha;

};

#endif // UI_SELECT