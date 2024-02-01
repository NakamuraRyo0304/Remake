/*
 *	@File	UI_Play.cpp
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "UI_Play.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 UI_Play::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// �ԐF
const float UI_Play::COLOR_SPEED = 0.075f;	// �F�̕ύX���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				// ���N���X
	, m_selection{ TitleSelect::Start }		// �X�^�[�g
	, m_position{}							// ���W
	, m_color{}								// �`��F
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Play::~UI_Play()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Play::Initialize()
{
	// �X�v���C�g�̓o�^
	m_sprites->AddTextureData(L"Start", L"Resources/Textures/TitleScene/Start.dds");
	m_sprites->AddTextureData(L"Exit", L"Resources/Textures/TitleScene/Exit.dds");

	// ���W�̐ݒ�
	m_position.emplace(L"Start", SimpleMath::Vector2(1200.0f, 950.0f));
	m_position.emplace(L"Exit", SimpleMath::Vector2(1600.0f, 950.0f));

	// �F�̐ݒ�
	m_color.emplace(L"Start", SimpleMath::Vector4(0, 0, 0, 1));
	m_color.emplace(L"Exit", SimpleMath::Vector4(0, 0, 0, 1));
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Play::Update()
{
	auto& _input = Input::GetInstance()->GetKeyTrack();

	// �ǂ��炩���������甽�]����
	if (_input->IsKeyPressed(Keyboard::Keys::Right) ||
		_input->IsKeyPressed(Keyboard::Keys::Left))
	{
		m_selection = m_selection == Start ? Exit : Start;
	}

	// �I��ԍ��ɉ����ĐF�𕪂���
	if (m_selection == TitleSelect::Start)
	{
		m_color[L"Start"] = UserUtility::Lerp(m_color[L"Start"], RED_COLOR, COLOR_SPEED);
		m_color[L"Exit"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
	if (m_selection == TitleSelect::Exit)
	{
		m_color[L"Exit"] = UserUtility::Lerp(m_color[L"Exit"], RED_COLOR, COLOR_SPEED);
		m_color[L"Start"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Play::Draw()
{
	m_sprites->DrawTexture(L"Start", m_position[L"Start"] * GetScreenRate(),
		m_color[L"Start"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 298, 97));
	m_sprites->DrawTexture(L"Exit", m_position[L"Exit"] * GetScreenRate(),
		m_color[L"Exit"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 278, 97));
}