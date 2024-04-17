/*
 *	@File	UI_Clear.h
 *	@Brief	�N���AUI�B
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_CLEAR
#define UI_CLEAR

// �e�V�[���N���X
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Clear final : public IUserInterface
{
public:

	// �I���̎��
	enum SELECT { NEXT, RESTART, STAGES, LENGTH };

	// �X�v���C�g�ɑΉ�����\����
	struct Option
	{
		DirectX::SimpleMath::Vector2 pos;
		DirectX::SimpleMath::Vector4 color;
	};

public:

	// ���̑�����擾
	SELECT GetSelecion() const { return m_select; }
	// ���̑����ݒ�
	void SetSelection(const SELECT& selection) { m_select = selection; }

	// ����̏I���󋵂��擾����
	bool IsEndMoving() const { return is_endMoving; }

	// �R���X�g���N�^
	UI_Clear(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// �f�X�g���N�^
	~UI_Clear();
	// ������
	void Initialize() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:

	// �F�ύX���x
	static const float COLOR_SPEED;
	// �ŏIX���W
	static const float LAST_POS_X;

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;
	// �I�v�V����
	std::map<const wchar_t*, Option> m_options;
	// �I��
	SELECT m_select;
	// ����I���t���O
	bool is_endMoving;

private:

	/// <summary>
	/// �F��ύX����
	/// </summary>
	/// <param name="select">�Ԏ��ɂ���������</param>
	/// <returns>�Ȃ�</returns>
	void ChangeColor(const SELECT& select);

};

#endif // UI_CLEAR