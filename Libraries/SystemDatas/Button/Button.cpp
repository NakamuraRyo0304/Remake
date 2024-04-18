/*
 *	@File	Button.cpp
 *	@Brief	�}�E�X�N���b�N�œ��삷��{�^���B
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "Button.h"

// �R���X�g���N�^
Button::Button(const wchar_t* name, const wchar_t* image)
	:
	m_name(name),					// ���O
	m_baseRate(),					// �{��
	m_position(),					// ���W
	m_adder(),						// ���Z���W
	m_screenRate(),					// �X�N���[���{��
	m_size(),						// �؂���T�C�Y
	m_states{ State::Release }		// �{�^���̏��
{
	// �摜�̐ݒ�ƍ쐬
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(name, image);
}

// �f�X�g���N�^
Button::~Button()
{
	m_sprite.reset();
}

// ������
void Button::Initialize(SimpleMath::Vector2 position, SimpleMath::Vector2 rate, RECT_U rect,
	SimpleMath::Vector2 screenRate, XMVECTORF32 color)
{
	// ���W��ݒ�
	m_position = position * screenRate;
	// �X�e�[�^�X��������
	m_states = State::Release;
	// �g�嗦��ݒ�
	m_screenRate = screenRate;
	m_baseRate = m_rate = rate * screenRate;
	// �F��ݒ�
	m_color = color;
	// �摜�T�C�Y��ݒ�
	m_size = rect;
}

// �X�V
void Button::Update()
{
	auto& ms = Mouse::Get();
	auto& mt = Input::GetInstance()->GetMouseTrack();

	float right = static_cast<float>(m_size.right * m_rate.x);
	float left = static_cast<float>(m_size.bottom * m_rate.y);

	// �͈͊O�ɍs�����烊���[�X
	SimpleMath::Vector2 addPos = m_adder * m_screenRate;
	if ((m_position + addPos).x < ms.GetState().x && ms.GetState().x < (m_position + addPos).x + right &&
		(m_position + addPos).y < ms.GetState().y && ms.GetState().y < (m_position + addPos).y + left)
	{
		// �{�^�����N���b�N����
		if (mt->leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			m_states = State::Push;
		}
		else
		{
			m_states = State::Hover;
		}
	}
	else
	{
		m_states = State::Release;
	}
}

// �`��
void Button::Draw()
{
	SimpleMath::Vector2 addPos = m_adder * m_screenRate;
	m_sprite->DrawTexture(m_name, m_position + addPos, m_color, m_rate, { 0,0 } , m_size);
}

