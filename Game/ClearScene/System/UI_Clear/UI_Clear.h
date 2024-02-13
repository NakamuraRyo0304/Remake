/*
 *	@File	UI_Clear.h
 *	@Brief	�N���AUI�B
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_CLEAR
#define UI_CLEAR

//==============================================================================
// �e�V�[���N���X
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_Clear final : public IUserInterface
{
public:

	// �I��
	enum SELECT { NEXT, RESTART, STAGES, LENGTH };

	// �X�v���C�g�ɑΉ�����\����
	struct Option
	{
		DirectX::SimpleMath::Vector2 pos;
		DirectX::SimpleMath::Vector4 color;
	};

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprites;

	// �I�v�V����
	std::map<const wchar_t*, Option> m_options;

	// �I��
	SELECT m_select;

private:

	// �I��F
	static const DirectX::SimpleMath::Vector4 RED_COLOR;
	static const DirectX::SimpleMath::Vector4 BLACK_COLOR;

	// �F�ύX���x
	static const float COLOR_SPEED;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scS">��ʃT�C�Y</param>
	/// <param name="mscS">�ő�T�C�Y</param>
	/// <returns>�Ȃ�</returns>
	UI_Clear(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Clear();

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

private:

	/// <summary>
	/// �F��ύX����
	/// </summary>
	/// <param name="select">�Ԏ��ɂ���������</param>
	/// <returns>�Ȃ�</returns>
	void ChangeColor(const SELECT& select);

public:

	// ���̑�����擾
	const SELECT& GetSelecion() { return m_select; }

	// ���̑����ݒ�
	void SetSelection(const SELECT& selection) { m_select = selection; }
};

#endif // UI_CLEAR