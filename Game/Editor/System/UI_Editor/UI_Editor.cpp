/*
 *	@File	UI_Editor.cpp
 *	@Brief	エディタUI。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Editor.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using BN = UI_Editor::BUTTON_NAME;		// ボタンの名前

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Editor::UI_Editor(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// 基底クラス
	, m_buttons{}					// ボタン
	, is_clicks{}					// クリック判定
{
	m_buttons.push_back(std::make_unique<Button>(L"Load", L"Resources/Textures/Editor/Buttons/LoadButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Write", L"Resources/Textures/Editor/Buttons/WriteButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Sand", L"Resources/Textures/Editor/Buttons/SandButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Cloud", L"Resources/Textures/Editor/Buttons/CloudButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Coin", L"Resources/Textures/Editor/Buttons/CoinButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Air", L"Resources/Textures/Editor/Buttons/AirButton.dds"));
	m_buttons.push_back(std::make_unique<Button>(L"Chara", L"Resources/Textures/Editor/Buttons/CharaButton.dds"));

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Editor::~UI_Editor()
{
	m_buttons.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Editor::Initialize()
{
	// ボタンのレクト				 // ボタンの拡大率
	RECT_U _bRect = { 0,0,256,256 }; SimpleMath::Vector2 _bRate = { 0.5f,0.5f };

	// 左側の位置		// 右側の位置
	float _L = 1638.0f;	float _R = 1776.0f;
	// 縦軸の位置		// 縦軸のオフセット
	float _Y = 54.0f;	float _OFF = 138.0f;

	// Position(X : _L or _R , Y : _Y + _OFF * n)
	m_buttons[BN::LoadFile]->Initialize(	{ _L, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::WriteFile]->Initialize(	{ _R, _Y + _OFF * 0}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Sand_bn]->Initialize(		{ _L, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Cloud_bn]->Initialize(	{ _R, _Y + _OFF * 1}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Coin_bn]->Initialize(		{ _L, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Air_bn]->Initialize(		{ _R, _Y + _OFF * 2}, _bRate, _bRect, GetScreenRate());
	m_buttons[BN::Player_bn]->Initialize(	{ _L, _Y + _OFF * 3}, _bRate, _bRect, GetScreenRate());
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Editor::Update()
{
	for (int i = 0; i < BN::Length; i++)
	{
		m_buttons[i]->Update();

		// ボタンがクリックされたらTrueを入れる
		is_clicks[i] = m_buttons[i]->GetState() == Button::State::Push;

		// ホバーされたら暗めにする
		bool _hover = m_buttons[i]->GetState() == Button::State::Hover;

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
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Editor::Draw()
{
	for (auto& button : m_buttons)
	{
		button->Draw();
	}
}
