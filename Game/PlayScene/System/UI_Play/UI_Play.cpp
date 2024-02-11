/*
 *	@File	UI_Play.cpp
 *	@Brief	プレイUI。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/Common/DrawNumber/DrawNumber.h"
#include "Game/PlayScene/System/UI_Play/UI_PlayArea/UI_PlayArea.h"
#include "UI_Play.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using ValDigits = DrawNumber::Digits;		// 数字のディジット

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				// 基底クラス
	, m_coinNum{}							// コイン枚数
{
	// エリア作成
	m_area = std::make_unique<UI_PlayArea>();

	// 数字作成
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
	m_nums->reset();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Play::Initialize()
{
	// エリアの設定
	m_area->SetPosition(SimpleMath::Vector2(1665.0f, 0.0f));
	m_area->SetColor(SimpleMath::Vector4::One * 0.5f);

	// 数字の設定
	m_nums[0]->SetPosition(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 320.0f));
	m_nums[0]->SetColor({ 0,0,0,1 });
	m_nums[1]->SetPosition(
		m_area->GetPosition() + SimpleMath::Vector2(128.0f, 320.0f));
	m_nums[1]->SetColor({ 0,0,0,1 });

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
	// エリアを描画
	m_area->Draw(GetScreenRate());

	// コインの枚数を描画
	m_nums[0]->Draw(m_coinNum, ValDigits::Ten);
	m_nums[1]->Draw(m_coinNum, ValDigits::One);
}
