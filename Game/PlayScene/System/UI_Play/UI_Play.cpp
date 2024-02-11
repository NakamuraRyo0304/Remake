/*
 *	@File	UI_Play.cpp
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
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
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");

	// ���W�̐ݒ�
	m_position.emplace(L"Area", SimpleMath::Vector2(1665.0f, 0.0f));

	// �F�̐ݒ�
	m_color.emplace(L"Area", SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Play::Update()
{
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Play::Draw()
{
	m_sprites->DrawTexture(L"Area",
		m_position[L"Area"] * GetScreenRate(), m_color[L"Area"],
		SimpleMath::Vector2::One * GetScreenRate(), SimpleMath::Vector2::Zero);
}
