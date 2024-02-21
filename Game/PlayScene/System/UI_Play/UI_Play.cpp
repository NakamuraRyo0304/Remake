/*
 *	@File	UI_Play.cpp
 *	@Brief	プレイUI。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Game/PlayScene/System/UI_Play/UI_CoinNum/UI_CoinNum.h"
#include "Game/PlayScene/System/UI_Play/UI_PlayArea/UI_PlayArea.h"
#include "UI_Play.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector4 UI_Play::BLACK = SimpleMath::Vector4(0, 0, 0, 1);	// 黒
const SimpleMath::Vector4 UI_Play::WHITE = SimpleMath::Vector4(1, 1, 1, 1);	// 白

//==============================================================================
// コンストラクタ
//==============================================================================
UI_Play::UI_Play(SimpleMath::Vector2 scS, SimpleMath::Vector2 mscs)
	: IUserInterface(scS, mscs)				                                // 基底クラス
	, m_coinNum{}							                                // コイン枚数
{
	// エリア作成
	m_area = std::make_unique<UI_PlayArea>();

	// 数字作成
	m_coins = std::make_unique<UI_CoinNum>();

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
UI_Play::~UI_Play()
{
	m_area.reset();
}

//==============================================================================
// 初期化処理
//==============================================================================
void UI_Play::Initialize()
{
	// エリアの設定
	m_area->Initialize(SimpleMath::Vector2(1665.0f, 0.0f), WHITE * 0.5f, GetScreenRate());

	// コイン数の設定
	m_coins->Initialize(
		m_area->GetPosition() + SimpleMath::Vector2(64.0f, 320.0f), BLACK, GetScreenRate());
	m_coins->SetCoinNum(m_coinNum);
	m_coins->SetCoinMaxNum(m_coinNum);
}

//==============================================================================
// 更新処理
//==============================================================================
void UI_Play::Update()
{
	m_coins->SetCoinNum(m_coinNum);
}

//==============================================================================
// 描画処理
//==============================================================================
void UI_Play::Draw()
{
	// エリアを描画
	m_area->Draw();

	// コイン数を描画
	m_coins->Draw();
}
