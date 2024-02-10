/*
 *  @File   MomentCanv.cpp
 *  @Brief  �N���A�����u�Ԃ̉摜��\������B
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "MomentCanv.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
MomentCanv::MomentCanv()
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
}

//==============================================================================
// �`��֐�
//==============================================================================
void MomentCanv::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector4 color,
	SimpleMath::Vector2 rate, SimpleMath::Vector2 origin, RECT_U rect)
{
	m_sprite->DrawTexture(L"PlayPic", pos, color, rate, origin, rect);
}
