/*
 *	@File	UI_Clear.cpp
 *	@Brief	�N���AUI�B
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Clear.h"

// �萔�̐ݒ�
const float UI_Clear::COLOR_SPEED = 0.05f;					// �F�̕ύX���x
const float UI_Clear::LAST_POS_X = 1550.0f;					// �ŏIX���W

// �R���X�g���N�^
UI_Clear::UI_Clear(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),		// ���N���X
	m_select(SELECT::NEXT),	// �Z���N�g
	m_options(),			// �I�v�V����
	is_endMoving(false)		// ����I���t���O
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// ����������
	Initialize();
}

// �f�X�g���N�^
UI_Clear::~UI_Clear()
{
	m_sprites.reset();
	m_options.clear();
}

// ������
void UI_Clear::Initialize()
{
	// �����̐ݒ�(�����p�X)
	m_sprites->AddTextureData(L"Next", L"Resources/Textures/Text/Nexttex.dds");
	m_sprites->AddTextureData(L"ReStart", L"Resources/Textures/Text/ReTrytex.dds");
	m_sprites->AddTextureData(L"Stages", L"Resources/Textures/Text/Selecttex.dds");

	// �������Ƃ̐ݒ�
	Option option = {};

	option.pos = { LAST_POS_X * 2,750.0f };
	option.color = UserUtility::Colors::WHITE;
	m_options.emplace(L"Next", option);

	option.pos.y += 100.0f;
	option.color = UserUtility::Colors::WHITE_A;
	m_options.emplace(L"ReStart", option);

	option.pos.y += 100.0f;
	m_options.emplace(L"Stages", option);
}

// �X�V
void UI_Clear::Update()
{
	// X���W���ړ�����
	for (auto& option : m_options)
	{
		option.second.pos.x =
			UserUtility::Lerp(option.second.pos.x, LAST_POS_X);
	}

	// �ړ�����������True
	if (static_cast<int>(m_options[L"Next"].pos.x) == static_cast<int>(LAST_POS_X))
	{
		is_endMoving = true;

		// �I��ԍ��ɉ����ĐF�𕪂���
		ChangeColor(m_select);
	}
}

// �`��
void UI_Clear::Draw()
{
	m_sprites->DrawTexture(L"Next", m_options[L"Next"].pos * GetScreenRate(),
		m_options[L"Next"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));

	m_sprites->DrawTexture(L"ReStart", m_options[L"ReStart"].pos * GetScreenRate(),
		m_options[L"ReStart"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));

	m_sprites->DrawTexture(L"Stages", m_options[L"Stages"].pos * GetScreenRate(),
		m_options[L"Stages"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));
}

// �F��ύX
void UI_Clear::ChangeColor(const SELECT& select)
{
	if (select == SELECT::NEXT)
	{
		m_options[L"Next"].color =
			UserUtility::Lerp(m_options[L"Next"].color, UserUtility::ColorsVector::WHITE, COLOR_SPEED);

		m_options[L"ReStart"].color = UserUtility::Colors::WHITE_A;
		m_options[L"Stages"].color = UserUtility::Colors::WHITE_A;
	}
	if (select == SELECT::RESTART)
	{
		m_options[L"ReStart"].color =
			UserUtility::Lerp(m_options[L"ReStart"].color, UserUtility::ColorsVector::WHITE, COLOR_SPEED);

		m_options[L"Stages"].color = UserUtility::Colors::WHITE_A;
		m_options[L"Next"].color = UserUtility::Colors::WHITE_A;
	}
	if (select == SELECT::STAGES)
	{
		m_options[L"Stages"].color =
			UserUtility::Lerp(m_options[L"Stages"].color, UserUtility::ColorsVector::WHITE, COLOR_SPEED);

		m_options[L"Next"].color = UserUtility::Colors::WHITE_A;
		m_options[L"ReStart"].color = UserUtility::Colors::WHITE_A;
	}
}
