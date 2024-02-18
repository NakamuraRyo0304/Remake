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
const SimpleMath::Vector4 UI_Clear::WHITE = SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);// 原色
const SimpleMath::Vector4 UI_Clear::THINW = SimpleMath::Vector4(0.4f, 0.4f, 0.4f, 0.4f);// 薄色
const float UI_Clear::COLOR_SPEED = 0.075f;	// 色の変更速度
const float UI_Clear::LAST_POS_X = 1550.0f;	// 最終X座標

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Clear::UI_Clear(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)		// 基底クラス
	, m_select{ SELECT::NEXT }		// セレクト
	, m_options{}					// オプション
	, is_endMoving{ false }			// 動作終了フラグ
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
	m_sprites->AddTextureData(L"Next", L"Resources/Textures/Text/Nexttex.dds");
	m_sprites->AddTextureData(L"ReStart", L"Resources/Textures/Text/ReTrytex.dds");
	m_sprites->AddTextureData(L"Stages", L"Resources/Textures/Text/Selecttex.dds");

	// 文字ごとの設定
	Option _opt = {};
	_opt.pos = { LAST_POS_X * 2,750.0f }; _opt.color = WHITE;
	m_options.emplace(L"Next", _opt);
	_opt.pos.y += 100.0f; _opt.color = THINW;
	m_options.emplace(L"ReStart", _opt);
	_opt.pos.y += 100.0f;
	m_options.emplace(L"Stages", _opt);
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Clear::Update()
{
	// X座標を移動する
	for (auto& option : m_options)
	{
		option.second.pos.x =
			UserUtility::Lerp(option.second.pos.x, LAST_POS_X, 0.1f);
	}

	// 移動完了したらTrue
	if (static_cast<int>(m_options[L"Next"].pos.x) == static_cast<int>(LAST_POS_X))
	{
		is_endMoving = true;

		// 選択番号に応じて色を分ける
		ChangeColor(m_select);
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Clear::Draw()
{
	m_sprites->DrawTexture(L"Next", m_options[L"Next"].pos * GetScreenRate(),
		m_options[L"Next"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));

	m_sprites->DrawTexture(L"ReStart", m_options[L"ReStart"].pos * GetScreenRate(),
		m_options[L"ReStart"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));

	m_sprites->DrawTexture(L"Stages", m_options[L"Stages"].pos * GetScreenRate(),
		m_options[L"Stages"].color, SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2::Zero, RECT_U(0, 0, 382, 128));
}

//==============================================================================
// 色変更
//==============================================================================
void UI_Clear::ChangeColor(const SELECT& select)
{
	if (select == SELECT::NEXT)
	{
		m_options[L"Next"].color =
			UserUtility::Lerp(m_options[L"Next"].color, WHITE, COLOR_SPEED);

		m_options[L"ReStart"].color = THINW;
		m_options[L"Stages"].color = THINW;
	}
	if (select == SELECT::RESTART)
	{
		m_options[L"ReStart"].color =
			UserUtility::Lerp(m_options[L"ReStart"].color, WHITE, COLOR_SPEED);

		m_options[L"Stages"].color = THINW;
		m_options[L"Next"].color = THINW;
	}
	if (select == SELECT::STAGES)
	{
		m_options[L"Stages"].color =
			UserUtility::Lerp(m_options[L"Stages"].color, WHITE, COLOR_SPEED);

		m_options[L"Next"].color = THINW;
		m_options[L"ReStart"].color = THINW;
	}
}
