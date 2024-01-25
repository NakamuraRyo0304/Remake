/*
 *	@File	UI_Title.cpp
 *	@Brief	�^�C�g��UI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "UI_Title.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector2 UI_Title::HOVER_RATE = { 0.1f, 0.1f };

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Title::UI_Title(SimpleMath::Vector2 screenRatio)
	: is_startClick{ false }
	, is_exitClick{ false }
{
	m_start = std::make_unique<Button>(L"Start", L"Resources/Textures/Buttons/Start.dds");
	m_exit  = std::make_unique<Button>(L"Exit",  L"Resources/Textures/Buttons/Exit.dds");

	m_start->Initialize(SimpleMath::Vector2(1000.0f,920.0f),
		SimpleMath::Vector2::One, { 0,0,288,97 }, screenRatio);
	m_exit->Initialize(SimpleMath::Vector2(1400.0f, 920.0f),
		SimpleMath::Vector2::One, { 0,0,224,97 }, screenRatio);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Title::~UI_Title()
{
	m_start.reset();
	m_exit.reset();
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Title::Update()
{
	m_start->Update();
	m_exit->Update();

	// �z�o�[���̏���
	if (m_start->GetState() == Button::State::Hover)
	{
		m_start->SetRate(SimpleMath::Vector2::One + HOVER_RATE);
		m_start->SetCorrectionPosition(SimpleMath::Vector2(-HOVER_RATE * 0.5f));
	}
	if (m_exit->GetState() == Button::State::Hover)
	{
		m_exit->SetRate(SimpleMath::Vector2::One + HOVER_RATE);
		m_exit->SetCorrectionPosition(SimpleMath::Vector2(-HOVER_RATE * 0.5f));
	}
	// �����[�X���̏���
	if (m_start->GetState() == Button::State::Release)
	{
		m_start->SetRate(SimpleMath::Vector2::One);
		m_start->SetCorrectionPosition(SimpleMath::Vector2::Zero);
	}
	if (m_exit->GetState() == Button::State::Release)
	{
		m_exit->SetRate(SimpleMath::Vector2::One);
		m_exit->SetCorrectionPosition(SimpleMath::Vector2::Zero);
	}

	is_startClick = m_start->GetState() == Button::State::Push;
	is_exitClick = m_exit->GetState() == Button::State::Push;
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Title::Draw()
{
	m_start->Draw();
	m_exit->Draw();
}
