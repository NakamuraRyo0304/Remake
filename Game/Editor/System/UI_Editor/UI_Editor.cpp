/*
 *	@File	UI_Editor.cpp
 *	@Brief	�G�f�B�^UI�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Editor.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using BN = UI_Editor::BUTTON_NAME;		// �{�^���̖��O

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Editor::UI_Editor(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// ���N���X
	, m_buttons{}					// �{�^��
	, is_clicks{}					// �N���b�N����
{
	m_buttons.push_back(std::make_unique<Button>(L"Load", L"Resources/Textures/Editor/Buttons/LoadButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Write", L"Resources/Textures/Editor/Buttons/WriteButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Sand", L"Resources/Textures/Editor/Buttons/SandButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Cloud", L"Resources/Textures/Editor/Buttons/CloudButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Coin", L"Resources/Textures/Editor/Buttons/CoinButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Air", L"Resources/Textures/Editor/Buttons/AirButton.dds"));

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Editor::~UI_Editor()
{
	m_buttons.clear();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Editor::Initialize()
{
	// �{�^���̃��N�g�Ɗg�嗦
	RECT_U _bRect = { 0,0,256,256 };
	SimpleMath::Vector2 _bRate = SimpleMath::Vector2::One * 0.5f;

	// Position(X + 138  Y + 138)
	m_buttons[BN::LoadFile]->Initialize({ 1638,54 }, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::WriteFile]->Initialize({ 1776,54 }, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Sand_bn]->Initialize({ 1638,192 }, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Cloud_bn]->Initialize({ 1776,192 }, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Coin_bn]->Initialize({ 1638,330 }, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Air_bn]->Initialize({ 1776,330 }, _bRate, _bRect, GetScreenRate());
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Editor::Update()
{
	for (int i = 0; i < BN::Length; i++)
	{
		m_buttons[i]->Update();

		// �{�^�����N���b�N���ꂽ��True������
		is_clicks[i] = m_buttons[i]->GetState() == Button::State::Push;

		// �z�o�[���ꂽ��Â߂ɂ���
		bool _hover = m_buttons[i]->GetState() == Button::State::Hover;

		// �{�^���̐F�̍X�V
		{
			if (is_clicks[i])
				m_buttons[i]->SetColor(SimpleMath::Color(0, 0, 0, 1));		// ��������
			else if (_hover)
				m_buttons[i]->SetColor(SimpleMath::Color(1, 1, 1, 0.5f));	// ��������
			else
				m_buttons[i]->SetColor(SimpleMath::Color(1, 1, 1, 1));		// ��������i���̐F�j
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Editor::Draw()
{
	for (auto& button : m_buttons)
	{
		button->Draw();
	}
}
