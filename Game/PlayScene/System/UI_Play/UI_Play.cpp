/*
 *	@File	UI_Play.cpp
 *	@Brief	プレイUI。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Button/Button.h"
#include "Game/PlayScene/System/UI_Play/UI_CoinNum/UI_CoinNum.h"
#include "Game/PlayScene/System/UI_Play/UI_PlayArea/UI_PlayArea.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Game/Common/DrawKeys/DrawKeys.h"
#include "UI_Play.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Play::WHITE = SimpleMath::Vector4::One;		// 白
const SimpleMath::Vector4 UI_Play::RED = SimpleMath::Vector4(1, 0, 0, 1);	// 赤

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				                                // 基底クラス
	, m_coinNum{}							                                // コイン枚数
	, m_coinTexPos{}														// 残りコイン枚数テキスト
	, m_cameraTexPos{}														// カメラテキスト
	, is_retryPush{ false }													// リトライボタンフラグ
{
	// エリア作成
	m_area = std::make_unique<UI_PlayArea>();

	// 数字作成
	m_coins = std::make_unique<UI_CoinNum>();

	// ボタンを作成
	m_retryButton = std::make_unique<Button>(L"RetryButton", L"Resources/Textures/UI_Play/RetryButton.dds");

	// キーオフセットを設定
	auto _offset = SimpleMath::Vector2(1728.0f, 384.0f);

	// キー作成
	m_keys[KEY_NAME::WKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/WKey.dds",
		SimpleMath::Vector2(64.0f, 0.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::SKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/SKey.dds",
		SimpleMath::Vector2(64.0f, 128.0f) + _offset, GetScreenRate());
	m_keys[KEY_NAME::AKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/AKey.dds",
		SimpleMath::Vector2(0.0f, 64.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::DKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/DKey.dds",
		SimpleMath::Vector2(128.0f, 64.0f) + _offset, GetScreenRate());

	// 画像描画作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
	m_coins.reset();
	m_keys.clear();
	m_sprite.reset();
	m_retryButton.reset();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Play::Initialize()
{
	// エリアの設定
	m_area->Initialize(SimpleMath::Vector2(1665.0f, 0.0f), WHITE * 0.5f, GetScreenRate());

	// リセットボタンの設定
	m_retryButton->Initialize(SimpleMath::Vector2(1856.0f, 0.0f), SimpleMath::Vector2::One * 0.25f,
		{ 0,0,256,256 }, GetScreenRate());

	// コイン数の設定
	m_coins->Initialize(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 128.0f), WHITE, { 0.5f,0.5f }, GetScreenRate());
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
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);

	// リセットボタンの更新
	m_retryButton->Update();
	is_retryPush = m_retryButton->GetState() == Button::State::Push;

	// キーの更新
	auto _key = Keyboard::Get().GetState();

	m_keys[KEY_NAME::WKEY]->SetColor(_key.W ? RED : WHITE);
	m_keys[KEY_NAME::SKEY]->SetColor(_key.S ? RED : WHITE);
	m_keys[KEY_NAME::AKEY]->SetColor(_key.A ? RED : WHITE);
	m_keys[KEY_NAME::DKEY]->SetColor(_key.D ? RED : WHITE);
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Play::Draw()
{
	// エリアを描画
	m_area->Draw();

	// コイン数を描画
	m_sprite->DrawTexture(L"CoinTex", m_coinTexPos,
		WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	m_coins->Draw();

	// キーを描画
	m_sprite->DrawTexture(L"CameraTex", m_cameraTexPos,
		WHITE, GetScreenRate() * 0.5f, { 0.0f, 0.0f }, { 0, 0, 256, 128 });
	for (auto& key : m_keys)
	{
		key.second->Draw();
	}

	// リセットボタンを描画
	m_retryButton->Draw();
}
