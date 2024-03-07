/*
 *	@File	UI_Title.cpp
 *	@Brief	タイトルUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "UI_Title.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;															// キーコード

//==============================================================================
// 定数の設定
//==============================================================================
const float UI_Title::COLOR_SPEED = 0.075f;												// 色の変更速度

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Title::UI_Title(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)															// 基底クラス
	, m_selection{ TitleSelect::Start }													// スタート
	, m_position{}																		// 座標
	, m_color{}																			// 描画色
	, is_anything{ false }																// 捜査状況監視フラグ
{
	m_sprites = std::make_unique<DrawSprite>();
	m_sprites->MakeSpriteBatch();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Title::~UI_Title()
{
	m_sprites.reset();
	m_position.clear();
	m_color.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Title::Initialize()
{
	// スプライトの登録
	m_sprites->AddTextureData(L"Start", L"Resources/Textures/Text/Start.dds");
	m_sprites->AddTextureData(L"Exit",  L"Resources/Textures/Text/Exit.dds");

	// 座標の設定
	m_position.emplace(L"Start", SimpleMath::Vector2(1500.0f, 800.0f));
	m_position.emplace(L"Exit", SimpleMath::Vector2(1500.0f, 950.0f));

	// 色の設定
	m_color.emplace(L"Start", SimpleMath::Vector4(1, 1, 1, 1));
	m_color.emplace(L"Exit", SimpleMath::Vector4(1, 1, 1, 1));

	is_anything = false;
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Title::Update()
{
	auto& _input = Input::GetInstance()->GetKeyTrack();

	// どちらかを押したら反転する
	if (_input->IsKeyPressed(KeyCode::Up)	|| _input->IsKeyPressed(KeyCode::Down) ||
		_input->IsKeyPressed(KeyCode::W)	|| _input->IsKeyPressed(KeyCode::S))
	{
		m_selection = m_selection == Start ? Exit : Start;
		is_anything = true;
	}
	else
	{
		is_anything = false;
	}

	// 選択番号に応じて色を分ける
	if (m_selection == TitleSelect::Start)
	{
		m_color[L"Start"] = UserUtility::Lerp(m_color[L"Start"], UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
		m_color[L"Exit"] = UserUtility::Colors::WHITE;
	}
	if (m_selection == TitleSelect::Exit)
	{
		m_color[L"Exit"] = UserUtility::Lerp(m_color[L"Exit"], UserUtility::ColorsVector::ORANGE, COLOR_SPEED);
		m_color[L"Start"] = UserUtility::Colors::WHITE;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Title::Draw()
{
	m_sprites->DrawTexture(L"Start", m_position[L"Start"] * GetScreenRate(),
		m_color[L"Start"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 298, 97));
	m_sprites->DrawTexture(L"Exit", m_position[L"Exit"] * GetScreenRate(),
		m_color[L"Exit"], SimpleMath::Vector2::One * GetScreenRate(),
		SimpleMath::Vector2(0.0f, 0.0f), RECT_U(0, 0, 278, 97));
}
