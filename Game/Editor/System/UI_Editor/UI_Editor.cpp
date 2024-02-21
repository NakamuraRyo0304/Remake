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

//==============================================================================
// エイリアス宣言
//==============================================================================
using BN = UI_Editor::BUTTON_NAME;		// ボタンの名前
using BS = Button::State;				// ボタンの状態

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Editor::UI_Editor(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		    // 基底クラス
	, m_buttons{}					    // ボタン
	, is_clicks{}					    // クリック判定
	, is_blindFlag{}				    // ボタンかくしフラグ
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
	auto _offset = SimpleMath::Vector2(128.0f, 896.0f);

	// キー作成
	m_keys[KEY_NAME::WKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/WKey.dds",
		SimpleMath::Vector2(64.0f, 0.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::SKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/SKey.dds",
		SimpleMath::Vector2(64.0f, 128.0f) + _offset, GetScreenRate());
	m_keys[KEY_NAME::AKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/AKey.dds",
		SimpleMath::Vector2(0.0f, 64.0f)   + _offset, GetScreenRate());
	m_keys[KEY_NAME::DKEY] = std::make_unique<DrawKeys>(L"Resources/Textures/Keys/DKey.dds",
		SimpleMath::Vector2(128.0f, 64.0f) + _offset, GetScreenRate());

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Editor::~UI_Editor()
{
	m_keys.clear();
	m_buttons.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Editor::Initialize()
{
	// フラグをオフ
	is_blindFlag = false;

	// ボタンのレクト				 // ボタンの拡大率
	RECT_U _bRect = { 0,0,256,256 }; SimpleMath::Vector2 _bRate = { 0.5f,0.5f };
	RECT_U _tRect = { 0,0,128,256 }; SimpleMath::Vector2 _tRate = { 0.4f,0.4f };

	// 左側の位置		// 右側の位置
	float _L = 1638.0f;	float _R = 1776.0f;	float _T = _L - static_cast<float>(_tRect.right + 10) * _tRate.x;
	// 縦軸の位置		// 縦軸のオフセット
	float _Y = 54.0f;	float _OFF = 138.0f;

	// 特殊ボタン
	m_buttons[BN::OC1_bn]->Initialize( { _T, _Y + _OFF * 0 }, _tRate, _tRect, GetScreenRate());
	m_buttons[BN::OC2_bn]->Initialize( { _T, _Y + _OFF * 1 }, _tRate, _tRect, GetScreenRate());

	// Position(X : _L or _R , Y : _Y + _OFF * n)
	m_buttons[BN::LoadFile]->Initialize(	{ _L, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::WriteFile]->Initialize(	{ _R, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Flozen_bn]->Initialize(	{ _L, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Cloud_bn]->Initialize(	{ _R, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Coin_bn]->Initialize(		{ _L, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Spike_bn]->Initialize(	{ _R, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Player_bn]->Initialize(	{ _L, _Y + _OFF * 3}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Goal_bn]->Initialize(		{ _R, _Y + _OFF * 3}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Air_bn]->Initialize(		{ _L, _Y + _OFF * 4}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Lift_bn]->Initialize(		{ _R, _Y + _OFF * 4}, _bRate, _bRect, GetScreenRate());

	// キーの初期設定
	for (auto& key : m_keys)
	{
		key.second->SetRate(SimpleMath::Vector2::One * 0.25f);
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Editor::Update()
{
	for (int i = 0; i < BN::Length_bn; i++)
	{
		m_buttons[i]->Update();

		// ボタンがクリックされたらTrueを入れる
		is_clicks[i] = m_buttons[i]->GetState() == BS::Push;

		// ホバーされたら暗めにする
		bool _hover = m_buttons[i]->GetState() == BS::Hover;

		// ボタンの色の更新
		{
			if (is_clicks[i])
				m_buttons[i]->SetColor(SimpleMath::Color(0, 0, 0, 1));		// 黒くする
			else if (_hover)
				m_buttons[i]->SetColor(SimpleMath::Color(1, 1, 1, 0.5f));	// 薄くする
			else
				m_buttons[i]->SetColor(SimpleMath::Color(1, 1, 1, 1));		// 白くする（元の色）
		}
	}

	// ボタン位置の更新
	MoveButtonPosition();

	// キーの更新
	auto _key = Keyboard::Get().GetState();

	m_keys[KEY_NAME::WKEY]->SetColor(_key.W ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::SKEY]->SetColor(_key.S ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::AKEY]->SetColor(_key.A ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
	m_keys[KEY_NAME::DKEY]->SetColor(_key.D ? SimpleMath::Vector4(1, 0, 0, 1) : SimpleMath::Vector4::One);
}

//==============================================================================
// 描画処理
//==============================================================================
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

//==============================================================================
// 加算座標を返す
//==============================================================================
const SimpleMath::Vector2& UI_Editor::GetAddPosition()
{
	if(UserUtility::IsNull(m_buttons[0].get())) return SimpleMath::Vector2::Zero;

	return m_buttons[0]->GetAdderPosition();
}

//==============================================================================
// ボタンの移動処理
//==============================================================================
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
		SimpleMath::Vector2 _now = m_buttons[i]->GetAdderPosition();
		float _x = UserUtility::EasedLerp(_now.x, is_blindFlag ? 288.0f : 0.0f, 0.4f);
		m_buttons[i]->SetAdderPosition(SimpleMath::Vector2(_x, m_buttons[i]->GetAdderPosition().y));
	}
}
