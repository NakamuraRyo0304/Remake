/*
 *  @File   MomentCanv.cpp
 *  @Brief  �N���A�����u�Ԃ̉摜��\������B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "MomentCanv.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector2 MomentCanv::LAST_POSITION = { 640.0f,460.0f };		// �ŏI���W
const SimpleMath::Vector2 MomentCanv::OUT_POSITION = { -2000.0f, -1500.0f };	// ��ʊO���W
const float MomentCanv::LAST_ROTATE = XMConvertToRadians(-385.0f);				// �ŏI��]
const float MomentCanv::SPEED_TO_LAST = 0.1f;									// ���x

//==============================================================================
// �R���X�g���N�^
//==============================================================================
MomentCanv::MomentCanv(SimpleMath::Vector2 screenRate)
	: m_position{}					// ���W
	, m_screenRate{ screenRate }	// ��ʔ䗦
{
	// �X�v���C�g�`��̍쐬
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
MomentCanv::~MomentCanv()
{
	m_sprite.reset();
}

//==============================================================================
// �������֐�
//==============================================================================
void MomentCanv::Initialize()
{
	// �X�v���C�g�̐ݒ�
	m_sprite->AddTextureData(L"PlayPic", L"Resources/Textures/ScreenShot/image.dds");

	// ��ʊO����n�߂�
	m_position = OUT_POSITION * m_screenRate;
}

//==============================================================================
// �X�V����
//==============================================================================
void MomentCanv::Update()
{
	// ���W�̈ړ�
	m_position = UserUtility::Lerp(m_position, LAST_POSITION, SPEED_TO_LAST);

	// �摜�̉�]
	m_sprite->CreateRotation(L"PlayPic",
		UserUtility::Lerp(m_sprite->GetRotate(L"PlayPic"), LAST_ROTATE, SPEED_TO_LAST));
}

//==============================================================================
// �`��֐�
//==============================================================================
void MomentCanv::Draw(SimpleMath::Vector4 color, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 origin, RECT_U rect)
{
	m_sprite->DrawTexture(L"PlayPic",
		m_position * m_screenRate, color, rate, origin * m_screenRate, rect);
}
