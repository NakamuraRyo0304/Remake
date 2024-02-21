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
#include "Game/Common/DrawKeys/DrawKeys.h"
#include "UI_Play.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 UI_Play::WHITE = SimpleMath::Vector4::One;		// ��

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

	// �L�[�I�t�Z�b�g��ݒ�
	auto _offset = SimpleMath::Vector2(128.0f, 896.0f);

	// �L�[�쐬
	m_keys[KEY_NAME::WKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/WKey.dds",
		SimpleMath::Vector2(64.0f, 0.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::SKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/SKey.dds",
		SimpleMath::Vector2(64.0f, 128.0f) + _offset, GetScreenRate());
	m_keys[KEY_NAME::AKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/AKey.dds",
		SimpleMath::Vector2(0.0f, 64.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::DKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/DKey.dds",
		SimpleMath::Vector2(128.0f, 64.0f) + _offset, GetScreenRate());

	// ����������
	Initialize();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
	m_coins.reset();
	m_keys.clear();
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
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 320.0f), WHITE, GetScreenRate());
	m_coins->SetCoinNum(m_coinNum);
	m_coins->SetCoinMaxNum(m_coinNum);

	// �L�[�̏����ݒ�
	for (auto& key : m_keys)
	{
		key.second->SetRate(SimpleMath::Vector2::One * 0.25f);
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);

	// �L�[�̍X�V
	auto _key = Keyboard::Get().GetState();

	m_keys[KEY_NAME::WKEY]->SetColor(_key.W ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::SKEY]->SetColor(_key.S ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::AKEY]->SetColor(_key.A ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::DKEY]->SetColor(_key.D ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
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

	// �L�[��`��
	for (auto& key : m_keys)
	{
		key.second->Draw();
	}
}
