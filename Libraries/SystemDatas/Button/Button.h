/*
 *	@File	Button.h
 *	@Brief	�}�E�X�N���b�N�œ��삷��{�^���B
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BUTTON
#define BUTTON

// �X�v���C�g�`��N���X���C���N���[�h
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

public:

	// �{�^���̏�Ԃ��擾
	State GetState() const { return m_states; }
	// �g�嗦��ݒ�
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }
	// ���̊g�嗦���擾
	const DirectX::SimpleMath::Vector2& GetBaseRate() { return m_baseRate; }
	// �F���擾
	const DirectX::SimpleMath::Color& GetColor() { return m_color; }
	// �F��ݒ�
	void SetColor(const DirectX::SimpleMath::Color& color) { m_color = color; }
	// �ړ����W���擾
	const DirectX::SimpleMath::Vector2& GetAdderPosition() { return m_adder; }
	// �ړ����W��ݒ�
	void SetAdderPosition(const DirectX::SimpleMath::Vector2 pos) { m_adder = pos; }

	// �R���X�g���N�^
	Button(const wchar_t* name,const wchar_t* image);
	// �f�X�g���N�^
	~Button();
	// ������
	void Initialize(DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 rate,
		RECT_U rect, DirectX::SimpleMath::Vector2 screenRatio, DirectX::XMVECTORF32 color = { 1,1,1,1 });
	// �X�V
	void Update();
	// �`��
	void Draw();

private:

	// �T�C�Y
	RECT_U m_size;
	// ���
	State m_states;
	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;
	// �{�^����
	const wchar_t* m_name;
	// ���W�E���Z���W�E���S���W
	DirectX::SimpleMath::Vector2 m_position, m_adder, m_origin;
	// �F
	DirectX::SimpleMath::Color m_color;
	// �g�嗦�E���̊g�嗦�E�X�N���[���{��
	DirectX::SimpleMath::Vector2 m_rate, m_baseRate, m_screenRate;

};

#endif // BUTTON