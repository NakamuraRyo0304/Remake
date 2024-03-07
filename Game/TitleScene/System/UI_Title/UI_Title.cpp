/*
 *	@File	UI_Title.cpp
 *	@Brief	�^�C�g��UI�B
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "UI_Title.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;															// �L�[�R�[�h

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float UI_Title::COLOR_SPEED = 0.075f;												// �F�̕ύX���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Title::UI_Title(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)															// ���N���X
	, m_selection{ TitleSelect::Start }													// �X�^�[�g
	, m_position{}																		// ���W
	, m_color{}																			// �`��F
	, is_anything{ false }																// �{���󋵊Ď��t���O
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Title::~UI_Title()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Title::Initialize()
{
	// �X�v���C�g�̓o�^
	m_sprites->AddTextureData(L"Start", L"Resources/Textures/Text/Start.dds");
	m_sprites->AddTextureData(L"Exit",  L"Resources/Textures/Text/Exit.dds");

	// ���W�̐ݒ�
	m_position.emplace(L"Start", SimpleMath::Vector2(1500.0f, 800.0f));
	m_position.emplace(L"Exit", SimpleMath::Vector2(1500.0f, 950.0f));

	// �F�̐ݒ�
	m_color.emplace(L"Start", SimpleMath::Vector4(1, 1, 1, 1));
	m_color.emplace(L"Exit", SimpleMath::Vector4(1, 1, 1, 1));

	is_anything = false;
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Title::Update()
{
	auto& _input = Input::GetInstance()->GetKeyTrack();

	// �ǂ��炩���������甽�]����
	if (_input->IsKeyPressed(KeyCode::Up)	|| _input->IsKeyPressed(KeyCode::Down) ||
		_input->IsKeyPressed(KeyCode::W)	|| _input->IsKeyPressed(KeyCode::S))
	{
		m_selection = m_selection == Start ? Exit : Start;
		is_anything = true;
	}
	else
	{
		is_anything = false;
	}

	// �I��ԍ��ɉ����ĐF�𕪂���
	if (m_selection == TitleSelect::Start)
	{
		m_color[L"Start"] = UserUtility::Lerp(m_color[L"Start"], UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
		m_color[L"Exit"] = UserUtility::Colors::WHITE;
	}
	if (m_selection == TitleSelect::Exit)
	{
		m_color[L"Exit"] = UserUtility::Lerp(m_color[L"Exit"], UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
		m_color[L"Start"] = UserUtility::Colors::WHITE;
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Title::Draw()
{
	m_sprites->DrawTexture(L"Start", m_position[L"Start"] * GetScreenRate(),
		m_color[L"Start"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 298, 97));
	m_sprites->DrawTexture(L"Exit", m_position[L"Exit"] * GetScreenRate(),
		m_color[L"Exit"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 278, 97));
}
