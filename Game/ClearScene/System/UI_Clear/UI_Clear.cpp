/*
 *	@File	UI_Clear.cpp
 *	@Brief	クリアUI。
 *	@Date	2023-02-13
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "UI_Clear.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Clear::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// 赤色
const SimpleMath::Vector4 UI_Clear::BLACK_COLOR = SimpleMath::Vector4(0, 0, 0, 1);	// 黒色
const float UI_Clear::COLOR_SPEED = 0.075f;	// 色の変更速度

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Clear::UI_Clear(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// 基底クラス
	, m_select{ SELECT::NEXT }		// セレクト
	, m_options{}					// オプション
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Clear::~UI_Clear()
{
	m_sprites.reset();
	m_options.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Clear::Initialize()
{
	// 文字の設定(文字パス)
	m_sprites->AddTextureData(L"Next", L"Resources/Textures/Text/Editor.dds");
	m_sprites->AddTextureData(L"ReStart", L"Resources/Textures/Text/Stage1tex.dds");
	m_sprites->AddTextureData(L"Stages", L"Resources/Textures/Text/Stage2tex.dds");

	// 文字ごとの設定
	Option _opt = {};
	_opt.pos = { 1500.0f,50.0f }; _opt.color = RED_COLOR;
	m_options.emplace(L"Next", _opt);
	_opt.pos = { 1500.0f,150.0f }; _opt.color = BLACK_COLOR;
	m_options.emplace(L"ReStart", _opt);
	_opt.pos = { 1500.0f,250.0f }; _opt.color = BLACK_COLOR;
	m_options.emplace(L"Stages", _opt);
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Clear::Update()
{
	// 選択番号に応じて色を分ける
	ChangeColor(m_select);
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Clear::Draw()
{
	m_sprites->DrawTexture(L"Next", m_options[L"Next"].pos * GetScreenRate(),
		m_options[L"Next"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"ReStart", m_options[L"ReStart"].pos * GetScreenRate(),
		m_options[L"ReStart"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
	m_sprites->DrawTexture(L"Stages", m_options[L"Stages"].pos * GetScreenRate(),
		m_options[L"Stages"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 382, 128));
}

//==============================================================================
// 色変更
//==============================================================================
void UI_Clear::ChangeColor(const SELECT& select)
{
	if (select == SELECT::NEXT)
	{
		m_options[L"Next"].color =
			UserUtility::Lerp(m_options[L"Next"].color, RED_COLOR, COLOR_SPEED);

		m_options[L"ReStart"].color = BLACK_COLOR;
		m_options[L"Stages"].color = BLACK_COLOR;
	}
	if (select == SELECT::RESTART)
	{
		m_options[L"ReStart"].color =
			UserUtility::Lerp(m_options[L"ReStart"].color, RED_COLOR, COLOR_SPEED);

		m_options[L"Stages"].color = BLACK_COLOR;
		m_options[L"Next"].color = BLACK_COLOR;
	}
	if (select == SELECT::STAGES)
	{
		m_options[L"Stages"].color =
			UserUtility::Lerp(m_options[L"Stages"].color, RED_COLOR, COLOR_SPEED);

		m_options[L"Next"].color = BLACK_COLOR;
		m_options[L"ReStart"].color = BLACK_COLOR;
	}
}
