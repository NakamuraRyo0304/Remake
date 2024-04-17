/*
 *	@File	TitleScene.cpp
 *	@Brief	タイトルシーン。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"											// プリコンパイル済みヘッダー
#include "Game/Cameras/AdminCamera/AdminCamera.h"			// 統合カメラ
#include "Game/TitleScene/System/UI_Title/UI_Title.h"		// ユーザインターフェース
#include "Libraries/SystemDatas/Timer/Timer.h"				// タイマー
#include "Game/TitleScene/System/MoveMonitor/MoveMonitor.h"	// モニター監視者

#include "Game/TitleScene/Objects/Sky_Title/Sky_Title.h"	// スカイドーム
#include "Game/TitleScene/Objects/Logo/Logo.h"				// タイトルロゴ

#include "Game/TitleScene/Objects/Bird_Title/Bird_Title.h"	// ペンギン
#include "Game/Common/Water/Water.h"						// 海
#include "Game/PlayScene/Objects/Iceberg/Iceberg.h"			// 氷山
#include "Game/Common/Island/Island.h"						// 孤島

#include "TitleScene.h"										// タイトルシーン

// 定数の設定
const float TitleScene::LOGO_FADE_IN_SPEED = 0.025f;		// ロゴフェードイン速度
const float TitleScene::LOGO_FADE_OUT_SPEED = 0.1f;			// ロゴフェードアウト速度

// エイリアス宣言
using KeyCode = Keyboard::Keys;				// キーコード
using CameraType = AdminCamera::Type;		// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;	// サウンドのタイプ

// コンストラクタ
TitleScene::TitleScene()
	:
	IScene()												// 基底クラスのコンストラクタ
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleSceneのコンストラクタが呼ばれました。\n");
}

// デストラクタ
TitleScene::~TitleScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleSceneのデストラクタが呼ばれました。\n");
	Finalize();
}

// 初期化
void TitleScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// ボリューム設定・音量再生開始(BGM・環境音)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, 0.25f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, RepeatType::LOOP);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,     RepeatType::LOOP);
}

// 更新
void TitleScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// ソフト終了
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::EXIT);
	}

	// シーン遷移
	if (IsCanUpdate())
	{
		// タイマーの更新
		m_timer->Update();

		// モニター監視者の更新
		m_moveMonitor->Update();

		// UIの更新
		m_ui->Update();

		// 何か入力があればタイマーを再スタート
		if (m_ui->IsAnything() || m_moveMonitor->IsMove())
		{
			m_timer->ReStart();
		}

		// タイマーが指定時間に達したら実行する
		if (m_timer->Alarm())
		{
			// ロゴをフェードアウトさせる
			m_logo->SetColor(UserUtility::Lerp(
				m_logo->GetColor(), SimpleMath::Vector4::One * QUARTER, LOGO_FADE_OUT_SPEED)
			);
		}
		else
		{
			// ロゴをフェードインさせる
			m_logo->SetColor(UserUtility::Lerp(
				m_logo->GetColor(), SimpleMath::Vector4::One, LOGO_FADE_IN_SPEED)
			);
		}

		// 選択音を鳴らす
		if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W)  || input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
			input->GetKeyTrack()->IsKeyPressed(KeyCode::Up) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
		{
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		}
		// スペースを押したら遷移する
		if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
		{
			m_ui->GetSelection() == UI_Title::Start ? ChangeScene(SCENE::SELECT) : ChangeScene(SCENE::EXIT);
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		}
	}

	// カメラの更新
	m_adminCamera->Update();

	// スカイ球の更新(カメラを中心にスカイ球をセットする　描画切れを防ぐ)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// トリの更新
	m_birdTitle->Update();

	// 氷山の更新
	m_iceberg->Update();
}

// 描画
void TitleScene::Draw()
{
	// レンダリング変数を取得
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// 空の描画
	m_sky->Draw(context, *states, view, projection);

	// トリの描画
	m_birdTitle->Draw(context, *states, view, projection);

	// 氷山の描画
	m_iceberg->Draw(context, *states, view, projection);

	// 孤島の描画
	m_island->Draw(context, *states, view, projection);

	// 水の描画
	m_water->Draw(view, projection);

	// UIの表示
	m_ui->Draw();

	// タイトルロゴの表示
	m_logo->Draw();


	// デバッグ描画
#if _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	//DebugDraw(*_states);
#endif
}

// 終了
void TitleScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_ui.reset();
	m_birdTitle.reset();
	m_water.reset();
	m_logo.reset();
	m_timer.reset();
	m_iceberg.reset();
	m_island.reset();
	m_moveMonitor.reset();
}

// 画面、デバイス依存の初期化
void TitleScene::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// スカイ球オブジェクト作成
	m_sky = std::make_unique<Sky_Title>();

	// UI作成
	m_ui = std::make_unique<UI_Title>(GetWindowSize(), GetFullHDSize());

	// トリオブジェクト作成
	m_birdTitle = std::make_unique<Bird_Title>();

	// 水作成
	m_water = std::make_unique<Water>();

	// ロゴ作成
	m_logo = std::make_unique<Logo>(GetWindowSize() / GetFullHDSize());

	// タイマー作成(10秒に設定)
	m_timer = std::make_unique<Timer>(Timer::Mode::limited, 10.0f);

	// 氷山作成
	m_iceberg = std::make_unique<Iceberg>(SimpleMath::Vector3(-20.0f, -25.0f, -50.0f), 10.0f, 0.0f);

	// 孤島作成
	m_island = std::make_unique<Island>(SimpleMath::Vector3(5.0f, -6.0f, 10.0f), 4.0f, 0.0f);

	// モニター監視者作成
	m_moveMonitor = std::make_unique<MoveMonitor>();
}

// シーン内の変数初期化関数
void TitleScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

	// 水の初期化
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// ロゴの初期化
	m_logo->Initialize({ 150.0f ,120.0f }, SimpleMath::Vector4::Zero, { 2,2 });

	// タイマーを開始
	m_timer->Start();

	// 孤島の行列を作成
	m_island->CreateWorldMatrix();
}

// デバッグ描画
void TitleScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// 文字の描画
	string.DrawFormatString(states, { 0,0 },  Colors::DarkGreen, L"TitleScene");
	string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", m_timer->GetCount());
}