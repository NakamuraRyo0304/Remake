/*
 *	@File	UI_Select.cpp
 *	@Brief	セレクトUI。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Select.h"

// 定数の設定
const float UI_Select::COLOR_SPEED = 0.075f; // 色の変更速度
const SimpleMath::Vector2 UI_Select::STAGE_TEX_POS = SimpleMath::Vector2(475.0f, 200.0f); // ステージ画像の座標
const float UI_Select::STAGE_TEX_RATE = 0.6f; // ステージ画像の拡大率
const float UI_Select::STAGE_TEX_SPAN = 185.0f; // ステージ番号の間隔

// コンストラクタ
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),				// 基底クラス
	m_stageSelection(1),			// ステージ１からスタート
	m_position(),					// 座標
	m_color(),						// 描画色
	m_stageAlpha()					// ステージアルファ値
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

// デストラクタ
UI_Select::~UI_Select()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

// 初期化
void UI_Select::Initialize()
{
	// 文字の設定(文字パス)
	m_sprites->AddTextureData(L"Editor", L"Resources/Textures/Text/Editor.dds");
	m_sprites->AddTextureData(L"Num1",   L"Resources/Textures/Text/Stage1tex.dds");
	m_sprites->AddTextureData(L"Num2",   L"Resources/Textures/Text/Stage2tex.dds");
	m_sprites->AddTextureData(L"Num3",   L"Resources/Textures/Text/Stage3tex.dds");
	m_sprites->AddTextureData(L"Num4",   L"Resources/Textures/Text/Stage4tex.dds");

	// 座標の設定
	m_position.emplace(L"Editor", SimpleMath::Vector2(50.0f, 50.0f));
	m_position.emplace(L"Num1",   SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Num2",   SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Num3",   SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Num4",   SimpleMath::Vector2(50.0f, 180.0f));

	float spanY = 0.0f;
	std::wstring first = L"Editor";
	std::wstring second = L"Num1";
	for (auto& pos : m_position)
	{
		// 最初のステージ１までは飛ばす
		if (pos.first == first || pos.first == second) continue;

		// 以降は均等に配置する
		spanY += STAGE_TEX_SPAN;
		pos.second.y += spanY;
	}

	// 色の設定
	m_color.emplace(L"Editor", UserUtility::Colors::BLACK);
	m_color.emplace(L"Num1",   UserUtility::Colors::BLACK);
	m_color.emplace(L"Num2",   UserUtility::Colors::BLACK);
	m_color.emplace(L"Num3",   UserUtility::Colors::BLACK);
	m_color.emplace(L"Num4",   UserUtility::Colors::BLACK);


	// ステージ画像パス
	m_stageAlpha = 0.75f;
	m_sprites->AddTextureData(L"StageE", L"Resources/Textures/Stages/StageE.dds");
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
		m_color[L"Editor"] = UserUtility::Lerp(m_color[L"Editor"], UserUtility::ColorsVector::RED, COLOR_SPEED);
		m_color[L"Num1"] = m_color[L"Num2"] = m_color[L"Num3"] =
			m_color[L"Num4"] = UserUtility::Colors::BLACK;
	}
	if(m_stageSelection == 1)
	{
		m_color[L"Num1"] = UserUtility::Lerp(m_color[L"Num1"], UserUtility::ColorsVector::RED, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num2"] = m_color[L"Num3"] =
			m_color[L"Num4"] = UserUtility::Colors::BLACK;
	}
	if(m_stageSelection == 2)
	{
		m_color[L"Num2"] = UserUtility::Lerp(m_color[L"Num2"], UserUtility::ColorsVector::RED, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num3"] =
			m_color[L"Num4"] = UserUtility::Colors::BLACK;
	}
	if(m_stageSelection == 3)
	{
		m_color[L"Num3"] = UserUtility::Lerp(m_color[L"Num3"], UserUtility::ColorsVector::RED, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num2"] =
			m_color[L"Num4"] = UserUtility::Colors::BLACK;
	}
	if(m_stageSelection == 4)
	{
		m_color[L"Num4"] = UserUtility::Lerp(m_color[L"Num4"], UserUtility::ColorsVector::RED, COLOR_SPEED);
		m_color[L"Editor"] = m_color[L"Num1"] = m_color[L"Num2"] =
			m_color[L"Num3"] = UserUtility::Colors::BLACK;
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
	case 0:
	{
		m_sprites->DrawTexture(L"StageE", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 1:
	{
		m_sprites->DrawTexture(L"Stage1", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 2:
	{
		m_sprites->DrawTexture(L"Stage2", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 3:
	{
		m_sprites->DrawTexture(L"Stage3", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
			SimpleMath::Vector2::Zero);
		return;
	}
	case 4:
	{
		m_sprites->DrawTexture(L"Stage4", STAGE_TEX_POS * GetScreenRate(),
			{ 1.0f,1.0f,1.0f,m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
			SimpleMath::Vector2::Zero);
		return;
	}
	default:
		return;
	}
}
