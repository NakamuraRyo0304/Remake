/*
 *	@File	UI_Editor.cpp
 *	@Brief	エディタUI。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/Common/DrawKeys/DrawKeys.h"
#include "UI_Editor.h"

// エイリアス宣言
using BN = UI_Editor::BUTTON_NAME;		// ボタンの名前
using BS = Button::State;				// ボタンの状態

// コンストラクタ
UI_Editor::UI_Editor(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),	    // 基底クラス
	m_buttons{},			// ボタン
	is_clicks{ false },		// クリック判定
	is_blindFlag(false)		// ボタンかくしフラグ
{
	// ボタン作成
	m_buttons.push_back(std::make_unique<Button>(L"Load"  , L"Resources/Textures/Editor/Buttons/LoadButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Write" , L"Resources/Textures/Editor/Buttons/WriteButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Flozen", L"Resources/Textures/Editor/Buttons/FlozenButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Cloud" , L"Resources/Textures/Editor/Buttons/CloudButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Coin"  , L"Resources/Textures/Editor/Buttons/CoinButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Air"   , L"Resources/Textures/Editor/Buttons/AirButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Chara" , L"Resources/Textures/Editor/Buttons/CharaButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Goal"  , L"Resources/Textures/Editor/Buttons/GoalButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Open"  , L"Resources/Textures/Editor/Buttons/OpenBar.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Close" , L"Resources/Textures/Editor/Buttons/CloseBar.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Spike" , L"Resources/Textures/Editor/Buttons/SpikeButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Lift"  , L"Resources/Textures/Editor/Buttons/LiftButton.dds"));

	// キーオフセットを設定
	auto offset = SimpleMath::Vector2(128.0f, 896.0f);

	// キー作成
	m_keys[KEY_NAME::WKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/WKey.dds",
		SimpleMath::Vector2(64.0f, 0.0f)   + offset, GetScreenRate());
	m_keys[KEY_NAME::SKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/SKey.dds",
		SimpleMath::Vector2(64.0f, 128.0f) + offset, GetScreenRate());
	m_keys[KEY_NAME::AKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/AKey.dds",
		SimpleMath::Vector2(0.0f, 64.0f)   + offset, GetScreenRate());
	m_keys[KEY_NAME::DKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/DKey.dds",
		SimpleMath::Vector2(128.0f, 64.0f) + offset, GetScreenRate());

	// 初期化処理
	Initialize();
}

// デストラクタ
UI_Editor::~UI_Editor()
{
	m_keys.clear();
	m_buttons.clear();
}

// 初期化
void UI_Editor::Initialize()
{
	// フラグをオフ
	is_blindFlag = false;

	// ボタンのレクトと拡大率
	RECT_U bRec = { 0,0,256,256 };
	SimpleMath::Vector2 bRate = { 0.5f,0.5f };
	// 特殊ボタンのレクトと拡大率
	RECT_U tRec = { 0,0,128,256 };
	SimpleMath::Vector2 tRate = { 0.4f,0.4f };

	// 左側の位置		// 右側の位置
	float l = 1638.0f;	float r = 1776.0f;
	// 特殊ボタンの位置
	float t = l - static_cast<float>(tRec.right + 10) * tRate.x;
	// 縦軸の位置		// 縦軸のオフセット
	float y = 54.0f;	float offset = 138.0f;

	// 特殊ボタン
	m_buttons[BN::OC1_bn]->Initialize( { t, y + offset * 0 }, tRate, tRec, GetScreenRate());
	m_buttons[BN::OC2_bn]->Initialize( { t, y + offset * 1 }, tRate, tRec, GetScreenRate());

	// Position(X : _L or _R , Y : _Y + _OFF * n)
	m_buttons[BN::LoadFile]->Initialize(	{ l, y + offset * 0}, bRate, bRec, GetScreenRate());
	m_buttons[BN::WriteFile]->Initialize(	{ r, y + offset * 0}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Flozen_bn]->Initialize(	{ l, y + offset * 1}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Cloud_bn]->Initialize(	{ r, y + offset * 1}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Coin_bn]->Initialize(		{ l, y + offset * 2}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Spike_bn]->Initialize(	{ r, y + offset * 2}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Player_bn]->Initialize(	{ l, y + offset * 3}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Goal_bn]->Initialize(		{ r, y + offset * 3}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Air_bn]->Initialize(		{ l, y + offset * 4}, bRate, bRec, GetScreenRate());
	m_buttons[BN::Lift_bn]->Initialize(		{ r, y + offset * 4}, bRate, bRec, GetScreenRate());

	// キーの初期設定
	for (auto& key : m_keys)
	{
		key.second->SetRate(SimpleMath::Vector2::One * 0.25f);
	}
}

// 更新
void UI_Editor::Update()
{
	for (int i = 0; i < BN::Length_bn; i++)
	{
		m_buttons[i]->Update();

		// ボタンがクリックされたらTrueを入れる
		is_clicks[i] = m_buttons[i]->GetState() == BS::Push;

		// ホバーされたら暗めにする
		bool hover = m_buttons[i]->GetState() == BS::Hover;

		// ボタンの色の更新
		{
			if (is_clicks[i])
				m_buttons[i]->SetColor(UserUtility::Colors::BLACK);			// 黒くする
			else if (hover)
				m_buttons[i]->SetColor(UserUtility::Colors::WHITE * 0.5f);	// 薄くする
			else
				m_buttons[i]->SetColor(UserUtility::Colors::WHITE);			// 白くする（元の色）
		}
	}

	// ボタン位置の更新
	MoveButtonPosition();

	// キーの更新
	auto key = Keyboard::Get().GetState();

	m_keys[KEY_NAME::WKEY]->SetColor(key.W ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::SKEY]->SetColor(key.S ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::AKEY]->SetColor(key.A ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
	m_keys[KEY_NAME::DKEY]->SetColor(key.D ? UserUtility::Colors::RED : UserUtility::Colors::WHITE);
}

// 描画
void UI_Editor::Draw()
{
	for (auto& button : m_buttons)
	{
		// オープンクローズボタンは別途処理
		if (button == m_buttons[BN::OC1_bn] || button == m_buttons[BN::OC2_bn]) continue;

		button->Draw();
	}

	// 表示非表示ボタン
	if (is_blindFlag)
	{
		m_buttons[BN::OC1_bn]->Draw();
	}
	else
	{
		m_buttons[BN::OC2_bn]->Draw();
	}

	// キーを描画
	for (auto& key : m_keys)
	{
		key.second->Draw();
	}
}

// 加算座標を返す
const SimpleMath::Vector2& UI_Editor::GetAddPosition()
{
	if(UserUtility::IsNull(m_buttons[0].get())) return SimpleMath::Vector2::Zero;

	return m_buttons[0]->GetAdderPosition();
}

// ボタンの移動処理
void UI_Editor::MoveButtonPosition()
{
	// 開くを押したら隠すフラグをFalseにする
	if (is_clicks[BN::OC1_bn])
	{
		is_blindFlag = false;
	}
	// 閉じるを押したら隠すフラグをTrueにする
	if (is_clicks[BN::OC2_bn])
	{
		is_blindFlag = true;
	}

	// 状態に応じてボタンを動かす
	for (int i = 0; i < BN::Length_bn; i++)
	{
		SimpleMath::Vector2 nowPosition = m_buttons[i]->GetAdderPosition();
		float xPosition = UserUtility::EasedLerp(nowPosition.x, is_blindFlag ? 288.0f : 0.0f, 0.4f);
		m_buttons[i]->SetAdderPosition(SimpleMath::Vector2(xPosition, m_buttons[i]->GetAdderPosition().y));
	}
}
