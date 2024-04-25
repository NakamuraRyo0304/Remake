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
const SimpleMath::Vector2 UI_Select::STAGE_TEX_POS =
	SimpleMath::Vector2(475.0f, 200.0f); // ステージ画像の座標
const float UI_Select::STAGE_TEX_RATE = 0.6f; // ステージ画像の拡大率
const float UI_Select::STAGE_TEX_SPAN = 185.0f; // ステージ番号の間隔

// コンストラクタ
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	:
	BaseUI(scS, mscs),		// 基底クラス
	m_selection(1),			// ステージ１からスタート
	m_position(),			// 座標
	m_color(),				// 描画色
	m_stageAlpha()			// ステージアルファ値
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
	m_sprites->AddTextureData(L"Text0", L"Resources/Textures/Text/Editor.dds");
	m_sprites->AddTextureData(L"Text1", L"Resources/Textures/Text/Stage1tex.dds");
	m_sprites->AddTextureData(L"Text2", L"Resources/Textures/Text/Stage2tex.dds");
	m_sprites->AddTextureData(L"Text3", L"Resources/Textures/Text/Stage3tex.dds");
	m_sprites->AddTextureData(L"Text4", L"Resources/Textures/Text/Stage4tex.dds");

	// 座標の設定
	m_position.emplace(L"Text0", SimpleMath::Vector2(35.0f, 50.0f));
	m_position.emplace(L"Text1", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text2", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text3", SimpleMath::Vector2(50.0f, 180.0f));
	m_position.emplace(L"Text4", SimpleMath::Vector2(50.0f, 180.0f));

	// 色の設定
	m_color.emplace(L"Text0", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text1", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text2", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text3", UserUtility::Colors::WHITE_A);
	m_color.emplace(L"Text4", UserUtility::Colors::WHITE_A);

	float spanY = 0.0f;
	std::wstring first  = L"Text0";
	std::wstring second = L"Text1";
	for (auto& pos : m_position)
	{
		// 最初のステージ１までは飛ばす
		if (pos.first == first || pos.first == second) continue;

		// 以降は均等に配置する
		spanY += STAGE_TEX_SPAN;
		pos.second.y += spanY;
	}


	// ステージ画像パス
	m_stageAlpha = 0.75f;
	m_sprites->AddTextureData(L"Stage0", L"Resources/Textures/Stages/StageE.dds");
	m_sprites->AddTextureData(L"Stage1", L"Resources/Textures/Stages/Stage1.dds");
	m_sprites->AddTextureData(L"Stage2", L"Resources/Textures/Stages/Stage2.dds");
	m_sprites->AddTextureData(L"Stage3", L"Resources/Textures/Stages/Stage3.dds");
	m_sprites->AddTextureData(L"Stage4", L"Resources/Textures/Stages/Stage4.dds");
}

// 更新
void UI_Select::Update()
{
	// 色をリセット
	ResetColors();

	// 選択中の項目を赤色に変更
	for (int i = 0; i < 5; ++i)
	{
		if (i != m_selection) continue;

		std::wstring text = L"Text" + std::to_wstring(i);
		m_color[text] = UserUtility::Lerp(m_color[text],
			UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
	}
}

// 描画
void UI_Select::Draw()
{
	// 文字を描画
	for (int i = 0; i < 5; ++i)
	{
		std::wstring text = L"Text" + std::to_wstring(i);
		m_sprites->DrawTexture(text, m_position[text] * GetScreenRate(),
			m_color[text], SimpleMath::Vector2::One * GetScreenRate(),
			SimpleMath::Vector2::Zero, RECT_EDIT);
	}

	// ステージ画像を描画
	std::wstring stage = L"Stage" + std::to_wstring(m_selection);
	m_sprites->DrawTexture(stage, STAGE_TEX_POS * GetScreenRate(),
		{ 1.0f, 1.0f, 1.0f, m_stageAlpha }, GetScreenRate() * STAGE_TEX_RATE,
		SimpleMath::Vector2::Zero);
}

// 色をリセットする
void UI_Select::ResetColors()
{
	// 選択番号に応じて色を分ける
	for (int i = 0; i < 5; ++i)
	{
		std::wstring text = L"Text" + std::to_wstring(i);
		m_color[text] = UserUtility::Lerp(m_color[text],
			UserUtility::ColorsVector::WHITE, COLOR_SPEED);
	}
}
