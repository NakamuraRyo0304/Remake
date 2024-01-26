/*
 *	@File	UI_Title.cpp
 *	@Brief	�^�C�g��UI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Title.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float UI_Title::RELEASE_ALPHA = 0.2f;		// �����[�X���̃A���t�@�l
const float UI_Title::ALPHA_FADE_SPEED = 0.1f;	// �A���t�@�̕ύX���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Title::UI_Title(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// ���N���X
	, is_startClick{ false }		// �X�^�[�g�t���O
	, is_exitClick{ false }			// �C�O�W�b�g�t���O
{
	m_start = std::make_unique<Button>(L"Start", L"Resources/Textures/TitleScene/Start.dds");
	m_exit  = std::make_unique<Button>(L"Exit",  L"Resources/Textures/TitleScene/Exit.dds");

	// ����������
	Initialize();
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
// ����������
//==============================================================================
void UI_Title::Initialize()
{
	m_start->Initialize(SimpleMath::Vector2(1200.0f, 920.0f),
		SimpleMath::Vector2::One, { 0,0,288,97 }, GetScreenRate());
	m_exit->Initialize(SimpleMath::Vector2(1600.0f, 920.0f),
		SimpleMath::Vector2::One, { 0,0,224,97 }, GetScreenRate());
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Title::Update()
{
	m_start->Update();
	m_exit->Update();

	// �X�^�[�g�{�^���̏���
	if (m_start->GetState() == Button::State::Release)
		m_start->SetColor(UserUtility::Lerp(m_start->GetColor(),
			SimpleMath::Color(1, 1, 1, RELEASE_ALPHA), ALPHA_FADE_SPEED));
	else
		m_start->SetColor(UserUtility::Lerp(m_start->GetColor(),
			SimpleMath::Color(1, 1, 1, 1), ALPHA_FADE_SPEED));

	// �C�O�W�b�g�{�^���̏���
	if (m_exit->GetState() == Button::State::Release)
		m_exit->SetColor(UserUtility::Lerp(m_exit->GetColor(),
			SimpleMath::Color(1, 1, 1, RELEASE_ALPHA), ALPHA_FADE_SPEED));
	else
		m_exit->SetColor(UserUtility::Lerp(m_exit->GetColor(),
			SimpleMath::Color(1, 1, 1, 1), ALPHA_FADE_SPEED));

	// �N���b�N�t���O��ێ�
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
