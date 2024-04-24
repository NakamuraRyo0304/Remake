/*
 *	@File	UI_Play.cpp
 *	@Brief	�v���CUI�B
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/PlayScene/System/UI_Play/CoinNum/CoinNum.h"
#include "Game/PlayScene/System/UI_Play/PlayArea/PlayArea.h"
#include "Game/Common/DrawKeys/DrawKeys.h"
#include "UI_Play.h"

// �R���X�g���N�^
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),			// ���N���X
	m_coinNum(),				// �R�C������
	m_coinTexPos(),				// �c��R�C�������e�L�X�g
	m_cameraTexPos(),			// �J�����e�L�X�g
	is_retryPush(false)			// ���g���C�{�^���t���O
{
	// �G���A�쐬
	m_area = std::make_unique<PlayArea>();
	// �����쐬
	m_coins = std::make_unique<CoinNum>();

	// �L�[�쐬�E�ݒ�
	auto offset = SimpleMath::Vector2(1728.0f, 384.0f);
	m_keys[KEY_NAME::WKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/WKey.dds",
		SimpleMath::Vector2(64.0f, 0.0f)   + offset, GetScreenRate());
	m_keys[KEY_NAME::SKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/SKey.dds",
		SimpleMath::Vector2(64.0f, 128.0f) + offset, GetScreenRate());
	m_keys[KEY_NAME::AKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/AKey.dds",
		SimpleMath::Vector2(0.0f, 64.0f)   + offset, GetScreenRate());
	m_keys[KEY_NAME::DKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/DKey.dds",
		SimpleMath::Vector2(128.0f, 64.0f) + offset, GetScreenRate());
	m_keys[KEY_NAME::RKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/UI_Play/RetryButton.dds",
		SimpleMath::Vector2(1888.0f, 32.0f), GetScreenRate());

	// �摜�`��쐬
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();

	// ����������
	Initialize();
}

// �f�X�g���N�^
UI_Play::~UI_Play()
{
	m_area.reset();
	m_coins.reset();
	m_keys.clear();
	m_sprite.reset();
}

// ������
void UI_Play::Initialize()
{
	// �G���A�̐ݒ�
	m_area->Initialize(SimpleMath::Vector2(1665.0f, 0.0f), UserUtility::Colors::WHITE, GetScreenRate());

	// �R�C�����̐ݒ�
	m_coins->Initialize(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 128.0f), UserUtility::Colors::WHITE, { 0.5f,0.5f }, GetScreenRate());
	m_coins->SetCoinNum(m_coinNum);
	m_coins->SetCoinMaxNum(m_coinNum);

	// �L�[�̏����ݒ�
	for (auto& key : m_keys)
	{
		key.second->SetRate(SimpleMath::Vector2::One * 0.25f);
	}

	// �X�v���C�g��o�^
	m_sprite->AddTextureData(L"CoinTex", L"Resources/Textures/Text/RemainingCoins.dds");
	m_coinTexPos = (m_area->GetPosition() + SimpleMath::Vector2(32.0f, 64.0f)) * GetScreenRate();
	m_sprite->AddTextureData(L"CameraTex", L"Resources/Textures/Text/Cameratex.dds");
	m_cameraTexPos = (m_area->GetPosition() + SimpleMath::Vector2(32.0f, 256.0f)) * GetScreenRate();

	// ���g���C�{�^���̐F��������
	m_keys[KEY_NAME::RKEY]->SetColor(UserUtility::Colors::WHITE);
}

// �X�V
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);

	// �L�[�̍X�V
	auto key = Keyboard::Get().GetState();
	m_keys[KEY_NAME::WKEY]->SetColor(key.W ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::SKEY]->SetColor(key.S ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::AKEY]->SetColor(key.A ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::DKEY]->SetColor(key.D ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);

	if (key.R)
	{
		m_keys[KEY_NAME::RKEY]->SetColor(UserUtility::Colors::RED);
		is_retryPush = true;
	}
}

// �`��
void UI_Play::Draw()
{
	// �G���A��`��
	m_area->Draw();

	// �R�C������`��
	m_sprite->DrawTexture(L"CoinTex", m_coinTexPos,
		UserUtility::Colors::WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	m_coins->Draw();

	// �L�[��`��
	m_sprite->DrawTexture(L"CameraTex", m_cameraTexPos,
		UserUtility::Colors::WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	for (auto& key : m_keys)
	{
		key.second->Draw();
	}
}
