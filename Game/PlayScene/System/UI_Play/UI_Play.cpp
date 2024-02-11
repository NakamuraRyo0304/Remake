/*
 *	@File	UI_Play.cpp
 *	@Brief	プレイUI。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Play.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Play::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// 赤色
const float UI_Play::COLOR_SPEED = 0.075f;	// 色の変更速度

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				// 基底クラス
	, m_position{}							// 座標
	, m_color{}								// 描画色
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Play::~UI_Play()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Play::Initialize()
{
	// スプライトの登録
	m_sprites->AddTextureData(L"Area", L"Resources/Textures/UI_Play/UI_Area.dds");

	// 座標の設定
	m_position.emplace(L"Area", SimpleMath::Vector2(1665.0f, 0.0f));

	// 色の設定
	m_color.emplace(L"Area", SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 0.5f));
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Play::Update()
{
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Play::Draw()
{
	m_sprites->DrawTexture(L"Area",
		m_position[L"Area"] * GetScreenRate(), m_color[L"Area"],
		SimpleMath::Vector2::One * GetScreenRate(), SimpleMath::Vector2::Zero);
}
