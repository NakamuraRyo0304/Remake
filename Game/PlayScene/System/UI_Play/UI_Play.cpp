/*
 *	@File	UI_Play.cpp
 *	@Brief	プレイUI。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/PlayScene/System/UI_Play/CoinNum/CoinNum.h"
#include "Game/PlayScene/System/UI_Play/PlayArea/PlayArea.h"
#include "Game/Common/DrawKeys/DrawKeys.h"
#include "UI_Play.h"

// コンストラクタ
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),			// 基底クラス
	m_coinNum(),				// コイン枚数
	m_coinTexPos(),				// 残りコイン枚数テキスト
	m_cameraTexPos(),			// カメラテキスト
	is_retryPush(false)			// リトライボタンフラグ
{
	// エリア作成
	m_area = std::make_unique<PlayArea>();
	// 数字作成
	m_coins = std::make_unique<CoinNum>();

	// キー作成・設定
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

	// 画像描画作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

// デストラクタ
UI_Play::~UI_Play()
{
	m_area.reset();
	m_coins.reset();
	m_keys.clear();
	m_sprite.reset();
}

// 初期化
void UI_Play::Initialize()
{
	// エリアの設定
	m_area->Initialize(SimpleMath::Vector2(1665.0f, 0.0f), UserUtility::Colors::WHITE, GetScreenRate());

	// コイン数の設定
	m_coins->Initialize(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 128.0f), UserUtility::Colors::WHITE, { 0.5f,0.5f }, GetScreenRate());
	m_coins->SetCoinNum(m_coinNum);
	m_coins->SetCoinMaxNum(m_coinNum);

	// キーの初期設定
	for (auto& key : m_keys)
	{
		key.second->SetRate(SimpleMath::Vector2::One * 0.25f);
	}

	// スプライトを登録
	m_sprite->AddTextureData(L"CoinTex", L"Resources/Textures/Text/RemainingCoins.dds");
	m_coinTexPos = (m_area->GetPosition() + SimpleMath::Vector2(32.0f, 64.0f)) * GetScreenRate();
	m_sprite->AddTextureData(L"CameraTex", L"Resources/Textures/Text/Cameratex.dds");
	m_cameraTexPos = (m_area->GetPosition() + SimpleMath::Vector2(32.0f, 256.0f)) * GetScreenRate();

	// リトライボタンの色を初期化
	m_keys[KEY_NAME::RKEY]->SetColor(UserUtility::Colors::WHITE);
}

// 更新
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);

	// キーの更新
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

// 描画
void UI_Play::Draw()
{
	// エリアを描画
	m_area->Draw();

	// コイン数を描画
	m_sprite->DrawTexture(L"CoinTex", m_coinTexPos,
		UserUtility::Colors::WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	m_coins->Draw();

	// キーを描画
	m_sprite->DrawTexture(L"CameraTex", m_cameraTexPos,
		UserUtility::Colors::WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	for (auto& key : m_keys)
	{
		key.second->Draw();
	}
}
