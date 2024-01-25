/*
 *	@File	Button.h
 *	@Brief	�}�E�X�N���b�N�œ��삷��{�^���B
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BUTTON
#define BUTTON

//==============================================================================
// �X�v���C�g�`��N���X���C���N���[�h
//==============================================================================
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"

class Button
{
public:

	// �{�^���̏��
	enum class State
	{
		Release,	// ����Ă�����
		Hover,		// �d�Ȃ��Ă�����
		Push,		// �����Ă�����
		Length,		// �v�f��
	};

private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

	// �{�^����
	const wchar_t* m_name;

	// ���W
	DirectX::SimpleMath::Vector2 m_position;

	// �␳���W
	DirectX::SimpleMath::Vector2 m_correctionPosition;

	// �F
	DirectX::SimpleMath::Color m_color;

	// �T�C�Y
	RECT_U m_size;

	// ���S���W
	DirectX::SimpleMath::Vector2 m_origin;

	// �g�嗦
	DirectX::SimpleMath::Vector2 m_rate;

	// ���
	State m_states;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="name">�{�^����</param>
	/// <param name="image">�摜�p�X</param>
	/// <returns>�Ȃ�</returns>
	Button(const wchar_t* name,const wchar_t* image);
	~Button();

	/// <summary>
	/// �����ݒ�
	/// </summary>
	/// <param name="position">������W</param>
	/// <param name="rate">�g�嗦</param>
	/// <param name="rect">�摜�T�C�Y</param>
	/// <param name="screenRatio">��ʔ䗦</param>
	/// <param name="color">�F�w��</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 rate,
		RECT_U rect,	DirectX::SimpleMath::Vector2 screenRatio, DirectX::XMVECTORF32 color = { 1,1,1,1 });

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();

	// �{�^���̏�Ԃ��擾
	const State& GetState() { return m_states; }

	// �g�嗦��ݒ�
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }

	// �␳���W��ݒ�
	void SetCorrectionPosition(const DirectX::SimpleMath::Vector2& pos) { m_correctionPosition = pos; }

private:

	/// <summary>
	/// �{�^���̏�Ԃ�ύX
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void ChangeButton();

};

#endif // BUTTON