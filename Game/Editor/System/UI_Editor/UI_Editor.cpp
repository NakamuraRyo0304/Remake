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
	, is_blindFlag{}				// �{�^���������t���O
{
	m_buttons.push_back(std::make_unique<Button>(L"Load", L"Resources/Textures/Editor/Buttons/LoadButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Write", L"Resources/Textures/Editor/Buttons/WriteButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Sand", L"Resources/Textures/Editor/Buttons/SandButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Cloud", L"Resources/Textures/Editor/Buttons/CloudButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Coin", L"Resources/Textures/Editor/Buttons/CoinButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Air", L"Resources/Textures/Editor/Buttons/AirButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Chara", L"Resources/Textures/Editor/Buttons/CharaButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Goal", L"Resources/Textures/Editor/Buttons/GoalButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Open", L"Resources/Textures/Editor/Buttons/OpenBar.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Close", L"Resources/Textures/Editor/Buttons/CloseBar.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Spike", L"Resources/Textures/Editor/Buttons/SpikeButton.dds"));

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
	// �t���O���I�t
	is_blindFlag = false;

	// �{�^���̃��N�g				 // �{�^���̊g�嗦
	RECT_U _bRect = { 0,0,256,256 }; SimpleMath::Vector2 _bRate = { 0.5f,0.5f };
	RECT_U _tRect = { 0,0,128,256 }; SimpleMath::Vector2 _tRate = { 0.4f,0.4f };

	// �����̈ʒu		// �E���̈ʒu
	float _L = 1638.0f;	float _R = 1776.0f;	float _T = _L - static_cast<float>(_tRect.right + 10) * _tRate.x;
	// �c���̈ʒu		// �c���̃I�t�Z�b�g
	float _Y = 54.0f;	float _OFF = 138.0f;

	// ����{�^��
	m_buttons[BN::OC1_bn]->Initialize( { _T, _Y + _OFF * 0 }, _tRate, _tRect, GetScreenRate());
	m_buttons[BN::OC2_bn]->Initialize( { _T, _Y + _OFF * 1 }, _tRate, _tRect, GetScreenRate());

	// Position(X : _L or _R , Y : _Y + _OFF * n)
	m_buttons[BN::LoadFile]->Initialize(	{ _L, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::WriteFile]->Initialize(	{ _R, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Sand_bn]->Initialize(		{ _L, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Cloud_bn]->Initialize(	{ _R, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Coin_bn]->Initialize(		{ _L, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Air_bn]->Initialize(		{ _R, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Player_bn]->Initialize(	{ _L, _Y + _OFF * 3}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Goal_bn]->Initialize(		{ _R, _Y + _OFF * 3}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Spike_bn]->Initialize(	{ _L, _Y + _OFF * 4}, _bRate, _bRect, GetScreenRate());

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

	MoveButtonPosition();
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Editor::Draw()
{
	for (auto& button : m_buttons)
	{
		// �I�[�v���N���[�Y�{�^���͕ʓr����
		if (button == m_buttons[BN::OC1_bn] || button == m_buttons[BN::OC2_bn]) continue;

		button->Draw();
	}

	// �\����\���{�^��
	if (is_blindFlag)
	{
		m_buttons[BN::OC1_bn]->Draw();
	}
	else
	{
		m_buttons[BN::OC2_bn]->Draw();
	}
}

//==============================================================================
// ���Z���W��Ԃ�
//==============================================================================
const SimpleMath::Vector2& UI_Editor::GetAddPosition()
{
	if(UserUtility::IsNull(m_buttons[0].get())) return SimpleMath::Vector2::Zero;

	return m_buttons[0]->GetAdderPosition();
}

//==============================================================================
// �{�^���̈ړ�����
//==============================================================================
void UI_Editor::MoveButtonPosition()
{
	// �J������������B���t���O��False�ɂ���
	if (is_clicks[BN::OC1_bn])
	{
		is_blindFlag = false;
	}
	// �������������B���t���O��True�ɂ���
	if (is_clicks[BN::OC2_bn])
	{
		is_blindFlag = true;
	}

	// ��Ԃɉ����ă{�^���𓮂���
	for (int i = 0; i < BN::Length; i++)
	{
		SimpleMath::Vector2 _now = m_buttons[i]->GetAdderPosition();
		float _x = UserUtility::EasedLerp(_now.x, is_blindFlag ? 288.0f : 0.0f, 0.4f);
		m_buttons[i]->SetAdderPosition(SimpleMath::Vector2(_x, m_buttons[i]->GetAdderPosition().y));
	}
}
