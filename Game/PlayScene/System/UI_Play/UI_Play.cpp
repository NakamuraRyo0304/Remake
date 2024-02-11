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
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Play::RED_COLOR = SimpleMath::Vector4(1, 0, 0, 1);	// 赤色
const float UI_Play::COLOR_SPEED = 0.075f;	// 色の変更速度

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
	// 数字作成
	for (int i = 0; i < 2; i++)
	{
		m_nums[i] = std::make_unique<DrawNumber>();
	}

	// エリア作成
	m_area = std::make_unique<UI_PlayArea>();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Play::~UI_Play()
{
	m_nums->reset();
	m_area.reset();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Play::Initialize()
{
	// 数字の設定
	m_nums[0]->SetPosition(SimpleMath::Vector2(1768.0f, 100.0f));
	m_nums[0]->SetColor({ 0,0,0,1 });
	m_nums[1]->SetPosition(SimpleMath::Vector2(1832.0f, 100.0f));
	m_nums[1]->SetColor({ 0,0,0,1 });

	// エリアの設定
	m_area->SetPosition(SimpleMath::Vector2(1665.0f, 0.0f));
	m_area->SetColor(SimpleMath::Vector4::One * 0.5f);

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
