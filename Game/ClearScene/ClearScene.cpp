/*
 *  @File   ClearScene.cpp
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"											// プリコンパイル済みヘッダー
#include "Libraries/UserUtility.h"							// ユーティリティ
#include "Game/ClearScene/System/UI_Clear/UI_Clear.h"		// ユーザインターフェース
#include "Libraries/SystemDatas/Timer/Timer.h"				// タイマー

#include "Game/ClearScene/System/ScoreBoard/ScoreBoard.h"	// スコアボード
#include "Game/ClearScene/Objects/MomentCanv/MomentCanv.h"	// プレイシーンのスクショ表示
#include "Game/ClearScene/Objects/BG_Clear/BG_Clear.h"		// 背景
#include "Game/ClearScene/Objects/Tape/Tape.h"				// テープオブジェクト
#include "Game/ClearScene/Objects/Seal/Seal.h"				// シールオブジェクト

#include "ClearScene.h"										// クリアシーン

// エイリアス宣言
using KeyCode = Keyboard::Keys;					// キーコード
using RepeatType = SoundManager::SE_MODE;		// サウンドのタイプ
using MouseClick = Mouse::ButtonStateTracker;	// マウスのクリック
using Selection = UI_Clear::SELECT;				// 次の選択

// コンストラクタ
ClearScene::ClearScene(float time, int coins, int stage, int max)
	:
	IScene(),					// 基底クラスのコンストラクタ
	m_clearTime(time),			// クリアタイム
	m_collectedCoin(coins),		// 集めたコイン数
	m_stageNumber(stage),		// ステージ番号
	m_maxNumber(max)			// 最大ステージ番号
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearSceneのコンストラクタが呼ばれました。\n");

	// 表示限界値でクランプ
	m_clearTime = UserUtility::Clamp(m_clearTime, 0.0f, 99.0f);
	m_collectedCoin = UserUtility::Clamp(m_collectedCoin, 0, 99);
}

// デストラクタ
ClearScene::~ClearScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearSceneのデストラクタが呼ばれました。\n");
	Finalize();
}

// 初期化
void ClearScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// ボリューム設定・音量再生開始(BGM・環境音)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_BGM_CLEAR, 0.5f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_CLEAR, RepeatType::LOOP);
}

// 更新
void ClearScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// セレクトに戻る
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::SELECT);
	}

	// シーン遷移
	if (IsCanUpdate())
	{
		// モーメントキャンバスの更新
		m_momentCanv->Update();

		// モーメントキャンバスがまだ動いていたらUIの処理をしない
		if (not m_momentCanv->IsEndMoving()) return;

		// タイム・コインのスコアを更新する
		m_direction->Update();
		if (m_direction->Alarm())
		{
			m_coinBoard->SetNumber(m_collectedCoin);
			m_timeBoard->SetNumber(static_cast<int>(m_clearTime));
		}
		else
		{
			m_coinBoard->SetNumber(static_cast<int>(UserUtility::Random(10.0, 60.0)));
			m_timeBoard->SetNumber(static_cast<int>(UserUtility::Random(10.0, 60.0)));
		}

		// UIの更新
		m_ui->Update();

		// UIの移動がまだ終わっていなければ処理をしない
		if (not m_ui->IsEndMoving()) return;

		// 次の遷移を選択する
		SceneSelection();
	}
}

// 描画
void ClearScene::Draw()
{
	// 背景の描画
	m_backGround->Draw();

	// モーメントキャンバスのレクトと拡大率、中心位置
	RECT_U rect =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 origin = FULL_HD * 0.5f;

	// モーメントキャンバスの描画
	m_momentCanv->Draw(SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, origin, rect);

	if (m_momentCanv->IsEndMoving())
	{
		// テープの描画
		m_tape[0]->Draw();
		m_tape[1]->Draw();

		// シールの描画
		m_seal[Sticker::Coin]->Draw();
		m_seal[Sticker::Clock]->Draw();

		// ボードの描画
		m_coinBoard->Draw();
		m_timeBoard->Draw();
	}

	// UIの描画
	m_ui->Draw();

	// デバッグ描画
#ifdef _DEBUG
	//DebugDraw(*_states);
#endif
}

// 終了
void ClearScene::Finalize()
{
	m_momentCanv.reset();
	m_ui.reset();
	m_direction.reset();
	m_coinBoard.reset();
	m_timeBoard.reset();
	m_backGround.reset();
	m_tape->reset();
	m_seal->reset();
}

// 画面、デバイス依存の初期化
void ClearScene::CreateWDResources()
{
	// モーメントキャンバス作成
	m_momentCanv = std::make_unique<MomentCanv>(GetWindowSize() / FULL_HD);

	// UI作成
	m_ui = std::make_unique<UI_Clear>(GetWindowSize(), FULL_HD);

	// スコアボード作成
	m_coinBoard = std::make_unique<ScoreBoard>();
	m_timeBoard = std::make_unique<ScoreBoard>();

	// ディレクトタイマー作成(3秒)
	m_direction = std::make_unique<Timer>(Timer::Mode::limited, 3.0f);

	// 背景作成
	m_backGround = std::make_unique<BG_Clear>();

	// テープ作成
	m_tape[0] = std::make_unique<Tape>();
	m_tape[1] = std::make_unique<Tape>();

	// シール作成
	m_seal[Sticker::Coin] = std::make_unique<Seal>(L"Resources/Textures/UI_Clear/coinSeal.dds");
	m_seal[Sticker::Clock] = std::make_unique<Seal>(L"Resources/Textures/UI_Clear/clockSeal.dds");
}

// シーン内の変数初期化関数
void ClearScene::SetSceneValues()
{
	// モーメントキャンバスの初期化
	m_momentCanv->Initialize();

	// 背景の初期化
	m_backGround->Initialize();

	// スコアボードの初期化(1文字分間隔をあける)
	m_coinBoard->Initialize({ 1500.0f,100.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / FULL_HD, 1.0);
	m_timeBoard->Initialize({ 1500.0f,250.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / FULL_HD, 1.0);

	// テープの初期化
	m_tape[0]->Initialize({ 110.0f,460.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-55.0f));
	m_tape[1]->Initialize({ 1150.0f,530.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-60.0f));

	// シールの初期化
	m_seal[Sticker::Coin]->Initialize({ 1400.0f, 160.0f }, SimpleMath::Vector2::One * 0.5f,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-55.0f));
	m_seal[Sticker::Clock]->Initialize({ 1420.0f, 312.0f }, SimpleMath::Vector2::One * 0.4f,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-53.0f));

	// タイマーを開始する
	m_direction->Start();
}

// デバッグ描画
void ClearScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// 文字の描画
	string.DrawFormatString(states, { 0,0 }, Colors::DarkGreen, L"ClearScene");
	string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Time::%.2f",m_clearTime);
	string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"Coin::%.d",m_collectedCoin);
	string.DrawFormatString(states, { 0,125 }, Colors::DarkGreen, L"Stage::%.d", m_stageNumber);
	string.DrawFormatString(states, { 0,150 }, Colors::DarkGreen, L"Direc::%.2f", m_direction->GetCount());
}

// シーン選択
void ClearScene::SceneSelection()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// シーンを選択する
	auto selection = m_ui->GetSelecion();
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		UserUtility::Increment(&selection);	// インクリメント
	}
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		UserUtility::Decrement(&selection);	// デクリメント
	}
	selection = UserUtility::LoopClamp(selection, Selection::NEXT, Selection::STAGES);
	m_ui->SetSelection(selection);

	// 次の遷移を決定
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		switch (m_ui->GetSelecion())
		{
		case Selection::NEXT:
			m_stageNumber++;
			m_stageNumber = UserUtility::LoopClamp(m_stageNumber, 1, m_maxNumber);
			ChangeScene(SCENE::PLAY);
			break;
		case Selection::RESTART:
			ChangeScene(SCENE::PLAY);
			break;
		case Selection::STAGES:
			ChangeScene(SCENE::SELECT);
		default:
			break;
		}
	}
}
