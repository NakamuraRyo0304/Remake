/*
 *	@File	UI_Play.cpp
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/PlayScene/System/UI_Play/UI_CoinNum/UI_CoinNum.h"
#include "Game/PlayScene/System/UI_Play/UI_PlayArea/UI_PlayArea.h"
#include "UI_Play.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 UI_Play::BLACK = SimpleMath::Vector4(0, 0, 0, 1);	// ��
const SimpleMath::Vector4 UI_Play::WHITE = SimpleMath::Vector4(1, 1, 1, 1);	// ��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				                                // ���N���X
	, m_coinNum{}							                                // �R�C������
{
	// �G���A�쐬
	m_area = std::make_unique<UI_PlayArea>();

	// �����쐬
	m_coins = std::make_unique<UI_CoinNum>();

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
}

//==============================================================================
// ����������
//==============================================================================
void UI_Play::Initialize()
{
	// �G���A�̐ݒ�
	m_area->Initialize(SimpleMath::Vector2(1665.0f, 0.0f), WHITE * 0.5f, GetScreenRate());

	// �R�C�����̐ݒ�
	m_coins->Initialize(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 320.0f), BLACK, GetScreenRate());
	m_coins->SetCoinNum(m_coinNum);
	m_coins->SetCoinMaxNum(m_coinNum);
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);
}

//==============================================================================
// �`�揈��
//==============================================================================
void UI_Play::Draw()
{
	// �G���A��`��
	m_area->Draw();

	// �R�C������`��
	m_coins->Draw();
}
