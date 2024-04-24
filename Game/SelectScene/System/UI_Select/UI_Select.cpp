/*
 *	@File	UI_Select.cpp
 *	@Brief	�Z���N�gUI�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Select.h"

// �萔�̐ݒ�
const float UI_Select::COLOR_SPEED = 0.075f; // �F�̕ύX���x
const SimpleMath::Vector2 UI_Select::STAGE_TEX_POS =
	SimpleMath::Vector2(475.0f, 200.0f); // �X�e�[�W�摜�̍��W
const float UI_Select::STAGE_TEX_RATE = 0.6f; // �X�e�[�W�摜�̊g�嗦
const float UI_Select::STAGE_TEX_SPAN = 185.0f; // �X�e�[�W�ԍ��̊Ԋu

// �R���X�g���N�^
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),		// ���N���X
	m_selection(1),			// �X�e�[�W�P����X�^�[�g
	m_position(),			// ���W
	m_color(),				// �`��F
	m_stageAlpha()			// �X�e�[�W�A���t�@�l
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// ����������
	Initialize();
}

// �f�X�g���N�^
UI_Select::~UI_Select()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

// ������
void UI_Select::Initialize()
{
	// �����̐ݒ�(�����p�X)
	m_sprites->AddTextureData(L"Text0", L"Resources/Textures/Text/Editor.dds");
	m_sprites->AddTextureData(L"Text1", L"Resources/Textures/Text/Stage1tex.dds");
	m_sprites->AddTextureData(L"Text2", L"Resources/Textures/Text/Stage2tex.dds");
	m_sprites->AddTextureData(L"Text3", L"Resources/Textures/Text/Stage3tex.dds");
	m_sprites->AddTextureData(L"Text4", L"Resources/Textures/Text/Stage4tex.dds");

	// ���W�̐ݒ�
	m_position.emplace(L"Text0", SimpleMath::Vector2(35.0f, 50.0f));
	m_position.emplace(L"Text1", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text2", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text3", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text4", SimpleMath::Vector2(50.0f, 180.0f));

	// �F�̐ݒ�
	m_color.emplace(L"Text0", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text1", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text2", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text3", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text4", UserUtility::Colors::WHITE_A);

	float spanY = 0.0f;
	std::wstring first  = L"Text0";
	std::wstring second = L"Text1";
	for (auto& pos : m_position)
	{
		// �ŏ��̃X�e�[�W�P�܂ł͔�΂�
		if (pos.first == first || pos.first == second) continue;

		// �ȍ~�͋ϓ��ɔz�u����
		spanY += STAGE_TEX_SPAN;
		pos.second.y += spanY;
	}


	// �X�e�[�W�摜�p�X
	m_stageAlpha = 0.75f;
	m_sprites->AddTextureData(L"Stage0", L"Resources/Textures/Stages/StageE.dds");
	m_sprites->AddTextureData(L"Stage1", L"Resources/Textures/Stages/Stage1.dds");
	m_sprites->AddTextureData(L"Stage2", L"Resources/Textures/Stages/Stage2.dds");
	m_sprites->AddTextureData(L"Stage3", L"Resources/Textures/Stages/Stage3.dds");
	m_sprites->AddTextureData(L"Stage4", L"Resources/Textures/Stages/Stage4.dds");
}

// �X�V
void UI_Select::Update()
{
	// �F�����Z�b�g
	ResetColors();

	// �I�𒆂̍��ڂ�ԐF�ɕύX
	for (int i = 0; i < 5; ++i)
	{
		if (i != m_selection) continue;

		std::wstring text = L"Text" + std::to_wstring(i);
		m_color[text] = UserUtility::Lerp(m_color[text],
			UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
	}
}

// �`��
void UI_Select::Draw()
{
	// ������`��
	for (int i = 0; i < 5; ++i)
	{
		std::wstring text = L"Text" + std::to_wstring(i);
		m_sprites->DrawTexture(text, m_position[text] * GetScreenRate(),
			m_color[text], SimpleMath::Vector2::One * GetScreenRate(),
			SimpleMath::Vector2::Zero, RECT_EDIT);
	}

	// �X�e�[�W�摜��`��
	std::wstring stage = L"Stage" + std::to_wstring(m_selection);
	m_sprites->DrawTexture(stage, STAGE_TEX_POS * GetScreenRate(),
		{ 1.0f, 1.0f, 1.0f, m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
		SimpleMath::Vector2::Zero);
}

// �F�����Z�b�g����
void UI_Select::ResetColors()
{
	// �I��ԍ��ɉ����ĐF�𕪂���
	for (int i = 0; i < 5; ++i)
	{
		std::wstring text = L"Text" + std::to_wstring(i);
		m_color[text] = UserUtility::Lerp(m_color[text],
			UserUtility::ColorsVector::WHITE, COLOR_SPEED);
	}
}
