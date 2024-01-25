/*
 *	@File	UI_Title.cpp
 *	@Brief	タイトルUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Title.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float UI_Title::RELEASE_ALPHA = 0.2f;		// リリース時のアルファ値
const float UI_Title::ALPHA_FADE_SPEED = 0.1f;	// アルファの変更速度

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Title::UI_Title(SimpleMath::Vector2 screenRatio)
	: is_startClick{ false }
	, is_exitClick{ false }
{
	m_start = std::make_unique<Button>(L"Start", L"Resources/Textures/Buttons/Start.dds");
	m_exit  = std::make_unique<Button>(L"Exit",  L"Resources/Textures/Buttons/Exit.dds");

	m_start->Initialize(SimpleMath::Vector2(1200.0f, 920.0f),
		SimpleMath::Vector2::One, { 0,0,288,97 }, screenRatio);
	m_exit->Initialize(SimpleMath::Vector2(1600.0f, 920.0f),
		SimpleMath::Vector2::One, { 0,0,224,97 }, screenRatio);
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Title::~UI_Title()
{
	m_start.reset();
	m_exit.reset();
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Title::Update()
{
	m_start->Update();
	m_exit->Update();

	// スタートボタンの処理
	if (m_start->GetState() == Button::State::Release)
		m_start->SetColor(UserUtility::Lerp(m_start->GetColor(),
			SimpleMath::Color(1, 1, 1, RELEASE_ALPHA), ALPHA_FADE_SPEED));
	else
		m_start->SetColor(UserUtility::Lerp(m_start->GetColor(),
			SimpleMath::Color(1, 1, 1, 1), ALPHA_FADE_SPEED));

	// イグジットボタンの処理
	if (m_exit->GetState() == Button::State::Release)
		m_exit->SetColor(UserUtility::Lerp(m_exit->GetColor(),
			SimpleMath::Color(1, 1, 1, RELEASE_ALPHA), ALPHA_FADE_SPEED));
	else
		m_exit->SetColor(UserUtility::Lerp(m_exit->GetColor(),
			SimpleMath::Color(1, 1, 1, 1), ALPHA_FADE_SPEED));

	// クリックフラグを保持
	is_startClick = m_start->GetState() == Button::State::Push;
	is_exitClick = m_exit->GetState() == Button::State::Push;
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Title::Draw()
{
	m_start->Draw();
	m_exit->Draw();
}
