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
const float UI_Select::COLOR_SPEED = 0.075f;	// 色の変更速度

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Select::UI_Select(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// 基底クラス
	, m_stageSelection{ 1 }			// ステージ１からスタート
	, m_position{}					// 座標
	, m_color{}						// 描画色
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
	// スプライトの登録
	m_sprites->AddTextureData(L"Stage1", L"Resources/Textures/SelectScene/Stage1.dds");
	m_sprites->AddTextureData(L"Stage2", L"Resources/Textures/SelectScene/Stage2.dds");
	m_sprites->AddTextureData(L"Stage3", L"Resources/Textures/SelectScene/Stage3.dds");

	// 座標の設定
	m_position.emplace(L"Stage1", SimpleMath::Vector2(50.0f, 50.0f));
	m_position.emplace(L"Stage2", SimpleMath::Vector2(50.0f, 150.0f));
	m_position.emplace(L"Stage3", SimpleMath::Vector2(50.0f, 250.0f));

	// 色の設定
	m_color.emplace(L"Stage1", SimpleMath::Vector4(0, 0, 0, 1));
	m_color.emplace(L"Stage2", SimpleMath::Vector4(0, 0, 0, 1));
	m_color.emplace(L"Stage3", SimpleMath::Vector4(0, 0, 0, 1));
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Select::Update()
{
	// 選択番号に応じて色を分ける
	if(m_stageSelection == 1)
	{
		m_color[L"Stage1"] = UserUtility::Lerp(m_color[L"Stage1"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage2"] = m_color[L"Stage3"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
	if(m_stageSelection == 2)
	{
		m_color[L"Stage2"] = UserUtility::Lerp(m_color[L"Stage2"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage1"] = m_color[L"Stage3"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
	if(m_stageSelection == 3)
	{
		m_color[L"Stage3"] = UserUtility::Lerp(m_color[L"Stage3"], RED_COLOR, COLOR_SPEED);
		m_color[L"Stage1"] = m_color[L"Stage2"] = SimpleMath::Vector4(0, 0, 0, 1);
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Select::Draw()
{
	m_sprites->DrawTexture(L"Stage1", m_position[L"Stage1"] * GetScreenRate(),
		m_color[L"Stage1"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Stage2", m_position[L"Stage2"] * GetScreenRate(),
		m_color[L"Stage2"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Stage3", m_position[L"Stage3"] * GetScreenRate(),
		m_color[L"Stage3"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
}
