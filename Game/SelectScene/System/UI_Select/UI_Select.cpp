/*
 *	@File	UI_Select.cpp
 *	@Brief	�Z���N�gUI�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Select.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 UI_Select::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// �ԐF
const float UI_Select::COLOR_SPEED = 0.075f;	// �F�̕ύX���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// ���N���X
	, m_stageSelection{ 1 }			// �X�e�[�W�P����X�^�[�g
	, m_position{}					// ���W
	, m_color{}						// �`��F
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Select::~UI_Select()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Select::Initialize()
{
	// �X�v���C�g�̓o�^
	m_sprites->AddTextureData(L"Stage1", L"Resources/Textures/SelectScene/Stage1.dds");
	m_sprites->AddTextureData(L"Stage2", L"Resources/Textures/SelectScene/Stage2.dds");
	m_sprites->AddTextureData(L"Stage3", L"Resources/Textures/SelectScene/Stage3.dds");

	// ���W�̐ݒ�
	m_position.emplace(L"Stage1", SimpleMath::Vector2(50.0f, 50.0f));
	m_position.emplace(L"Stage2", SimpleMath::Vector2(50.0f, 150.0f));
	m_position.emplace(L"Stage3", SimpleMath::Vector2(50.0f, 250.0f));

	// �F�̐ݒ�
	m_color.emplace(L"Stage1", SimpleMath::Vector4(0, 0, 0, 1));
	m_color.emplace(L"Stage2", SimpleMath::Vector4(0, 0, 0, 1));
	m_color.emplace(L"Stage3", SimpleMath::Vector4(0, 0, 0, 1));
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Select::Update()
{
	// �I��ԍ��ɉ����ĐF�𕪂���
	if(m_stageSelection == 1)
	{
		m_color[L"Stage1"] = UserUtility::Lerp(m_color[L"Stage1"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage2"] = m_color[L"Stage3"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
	if(m_stageSelection == 2)
	{
		m_color[L"Stage2"] = UserUtility::Lerp(m_color[L"Stage2"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage1"] = m_color[L"Stage3"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
	if(m_stageSelection == 3)
	{
		m_color[L"Stage3"] = UserUtility::Lerp(m_color[L"Stage3"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage1"] = m_color[L"Stage2"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Select::Draw()
{
	m_sprites->DrawTexture(L"Stage1", m_position[L"Stage1"] * GetScreenRate(),
		m_color[L"Stage1"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Stage2", m_position[L"Stage2"] * GetScreenRate(),
		m_color[L"Stage2"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Stage3", m_position[L"Stage3"] * GetScreenRate(),
		m_color[L"Stage3"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
}
