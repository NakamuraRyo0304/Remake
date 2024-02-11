/*
 *	@File	UI_Play.cpp
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "Game/PlayScene/System/UI_Play/UI_PlayArea/UI_PlayArea.h"
#include "UI_Play.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using ValDigits = DrawNumber::Digits;		// �����̃f�B�W�b�g

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				// ���N���X
	, m_coinNum{}							// �R�C������
{
	// �G���A�쐬
	m_area = std::make_unique<UI_PlayArea>();

	// �����쐬
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
	m_nums->reset();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Play::Initialize()
{
	// �G���A�̐ݒ�
	m_area->SetPosition(SimpleMath::Vector2(1665.0f, 0.0f));
	m_area->SetColor(SimpleMath::Vector4::One * 0.5f);

	// �����̐ݒ�
	m_nums[0]->SetPosition(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 320.0f));
	m_nums[0]->SetColor({ 0,0,0,1 });
	m_nums[1]->SetPosition(
		m_area->GetPosition() + SimpleMath::Vector2(128.0f, 320.0f));
	m_nums[1]->SetColor({ 0,0,0,1 });

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
	// �G���A��`��
	m_area->Draw(GetScreenRate());

	// �R�C���̖�����`��
	m_nums[0]->Draw(m_coinNum, ValDigits::Ten);
	m_nums[1]->Draw(m_coinNum, ValDigits::One);
}
