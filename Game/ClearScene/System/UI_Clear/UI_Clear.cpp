/*
 *	@File	UI_Select.cpp
 *	@Brief	セレクトUI。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Select.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Select::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// 赤色
const SimpleMath::Vector4 UI_Select::BLACK_COLOR = SimpleMath::Vector4(0, 0, 0, 1);	// 黒色
const float UI_Select::COLOR_SPEED = 0.075f;	// 色の変更速度
// ステージ画像の座標
const SimpleMath::Vector2 UI_Select::STAGE_TEX_POS = SimpleMath::Vector2(475.0f, 200.0f);

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// 基底クラス
	, m_stageSelection{ 1 }			// ステージ１からスタート
	, m_position{}					// 座標
	, m_color{}						// 描画色
	, m_stageAlpha{}				// ステージアルファ値
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Select::~UI_Select()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Select::Initialize()
{
	// 文字の設定(文字パス)
	m_sprites->AddTextureData(L"Editor", L"Resources/Textures/Text/Editor.dds");
	m_sprites->AddTextureData(L"Num1", L"Resources/Textures/Text/Stage1tex.dds");
	m_sprites->AddTextureData(L"Num2", L"Resources/Textures/Text/Stage2tex.dds");
	m_sprites->AddTextureData(L"Num3", L"Resources/Textures/Text/Stage3tex.dds");
	m_sprites->AddTextureData(L"Num4", L"Resources/Textures/Text/Stage4tex.dds");

	// 座標の設定
	m_position.emplace(L"Editor", SimpleMath::Vector2(50.0f, 50.0f));
	m_position.emplace(L"Num1", SimpleMath::Vector2(50.0f, 150.0f));
	m_position.emplace(L"Num2", SimpleMath::Vector2(50.0f, 250.0f));
	m_position.emplace(L"Num3", SimpleMath::Vector2(50.0f, 350.0f));
	m_position.emplace(L"Num4", SimpleMath::Vector2(50.0f, 450.0f));

	// 色の設定
	m_color.emplace(L"Editor", BLACK_COLOR);
	m_color.emplace(L"Num1", BLACK_COLOR);
	m_color.emplace(L"Num2", BLACK_COLOR);
	m_color.emplace(L"Num3", BLACK_COLOR);
	m_color.emplace(L"Num4", BLACK_COLOR);


	// ステージ画像パス
	m_stageAlpha = 0.75f;
	m_sprites->AddTextureData(L"Stage1", L"Resources/Textures/Stages/Stage1.dds");
	m_sprites->AddTextureData(L"Stage2", L"Resources/Textures/Stages/Stage2.dds");
	m_sprites->AddTextureData(L"Stage3", L"Resources/Textures/Stages/Stage3.dds");
	m_sprites->AddTextureData(L"Stage4", L"Resources/Textures/Stages/Stage4.dds");
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Select::Update()
{
	// 選択番号に応じて色を分ける
	if(m_stageSelection == 0)
	{
		m_color[L"Editor"] = UserUtility::Lerp(m_color[L"Editor"], RED_COLOR, COLOR_SPEED);
		m_color[L"Num1"] = m_color[L"Num2"] = m_color[L"Num3"] =
			m_color[L"Num4"] = BLACK_COLOR;
	}
	if(m_stageSelection == 1)
	{
		m_color[L"Num1"] = UserUtility::Lerp(m_color[L"Num1"], RED_COLOR, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num2"] = m_color[L"Num3"] =
			m_color[L"Num4"] = BLACK_COLOR;
	}
	if(m_stageSelection == 2)
	{
		m_color[L"Num2"] = UserUtility::Lerp(m_color[L"Num2"], RED_COLOR, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num3"] =
			m_color[L"Num4"] = BLACK_COLOR;
	}
	if(m_stageSelection == 3)
	{
		m_color[L"Num3"] = UserUtility::Lerp(m_color[L"Num3"], RED_COLOR, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num2"] =
			m_color[L"Num4"] = BLACK_COLOR;
	}
	if(m_stageSelection == 4)
	{
		m_color[L"Num4"] = UserUtility::Lerp(m_color[L"Num4"], RED_COLOR, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num2"] =
			m_color[L"Num3"] = BLACK_COLOR;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Select::Draw()
{
	m_sprites->DrawTexture(L"Editor", m_position[L"Editor"] * GetScreenRate(),
		m_color[L"Editor"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 768, 128));
	m_sprites->DrawTexture(L"Num1", m_position[L"Num1"] * GetScreenRate(),
		m_color[L"Num1"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Num2", m_position[L"Num2"] * GetScreenRate(),
		m_color[L"Num2"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Num3", m_position[L"Num3"] * GetScreenRate(),
		m_color[L"Num3"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Num4", m_position[L"Num4"] * GetScreenRate(),
		m_color[L"Num4"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));

	// ステージ画像を描画
	switch (m_stageSelection)
	{
	case 1:
	{
		m_sprites->DrawTexture(L"Stage1", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * 0.6f,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 2:
	{
		m_sprites->DrawTexture(L"Stage2", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * 0.6f,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 3:
	{
		m_sprites->DrawTexture(L"Stage3", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * 0.6f,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 4:
	{
		m_sprites->DrawTexture(L"Stage4", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * 0.6f,
			SimpleMath::Vector2::Zero);
		return;
	}
	default:
		return;
	}
}
