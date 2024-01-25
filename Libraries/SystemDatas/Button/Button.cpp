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

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Button::Button(const wchar_t* name, const wchar_t* image)
	: m_name{ name }
	, m_baseRate{}
	, m_position{}
	, m_size{}
{
	// �摜�̐ݒ�
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(name, image);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Button::~Button()
{
	m_sprite.reset();
}

//==============================================================================
// ����������
//==============================================================================
void Button::Initialize(SimpleMath::Vector2 position, SimpleMath::Vector2 rate, RECT_U rect,
	SimpleMath::Vector2 screenRatio, XMVECTORF32 color)
{
	// ���W��ݒ�
	m_position = position * screenRatio;

	// �X�e�[�^�X��������
	m_states = State::Release;

	// �g�嗦��ݒ�
	m_baseRate = m_rate = rate * screenRatio;

	// �F��ݒ�
	m_color = color;

	// �摜�T�C�Y��ݒ�
	m_size = rect;
}

//==============================================================================
// �X�V
//==============================================================================
void Button::Update()
{
	auto& _ms = Mouse::Get();
	auto& _mt = Input::GetInstance()->GetMouseTrack();

	float _right = static_cast<float>(m_size.right * m_rate.x);
	float _left = static_cast<float>(m_size.bottom * m_rate.y);

	// �͈͊O�ɍs�����烊���[�X
	if (m_position.x < _ms.GetState().x && _ms.GetState().x < m_position.x + _right &&
		m_position.y < _ms.GetState().y && _ms.GetState().y < m_position.y + _left)
	{
		// �{�^�����N���b�N����
		if (_mt->leftButton == Mouse::ButtonStateTracker::PRESSED)
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

//==============================================================================
// �`��
//==============================================================================
void Button::Draw()
{
	m_sprite->DrawTexture(m_name, m_position, m_color, m_rate, { 0,0 } , m_size);
}

