/*
 *	@File	UI_Select.h
 *	@Brief	�Z���N�gUI�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_SELECT
#define UI_SELECT

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Select final : public IUserInterface
{
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;

	// ���W
	std::map<const wchar_t*, DirectX::SimpleMath::Vector2> m_position;

	// �F
	std::map<const wchar_t*, DirectX::SimpleMath::Vector4> m_color;

	// �I���X�e�[�W�ԍ�
	int m_stageSelection;

	// �X�e�[�W�摜�A���t�@�l
	float m_stageAlpha;

private:

	// �F�ύX���x
	static const float COLOR_SPEED;

	// �X�e�[�W�ԍ��̊Ԋu
	static const float STAGE_TEX_SPAN;

	// �摜�̍��W
	static const DirectX::SimpleMath::Vector2 STAGE_TEX_POS;

	// �摜�̊g�嗦
	static const float STAGE_TEX_RATE;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Select(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Select();

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

	// �I�𒆂̃X�e�[�W�ԍ���ݒ�
	void SetSelectionNum(const int& num) { m_stageSelection = num; }

};

#endif // UI_SELECT