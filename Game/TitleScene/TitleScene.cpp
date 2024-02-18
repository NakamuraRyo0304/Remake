/*
 *	@File	TitleScene.cpp
 *	@Brief	タイトルシーン。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/TitleScene/System/UI_Title/UI_Title.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
// オブジェクト
#include "Game/TitleScene/Objects/Sky_Title/Sky_Title.h"
#include "Game/TitleScene/Objects/Bird_Title/Bird_Title.h"
#include "Game/Common/Water/Water.h"
#include "Game/TitleScene/Objects/Logo/Logo.h"
#include "Game/PlayScene/Objects/Iceberg/Iceberg.h"
#include "Game/Common/Island/Island.h"
#include "TitleScene.h"

//==============================================================================
// 定数の設定
//==============================================================================
const float TitleScene::LOGO_FADE_IN_SPEED = 0.025f;		// ロゴフェードイン速度
const float TitleScene::LOGO_FADE_OUT_SPEED = 0.1f;			// ロゴフェードアウト速度

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using CameraType = AdminCamera::Type;					// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ

//==============================================================================
// コンストラクタ
//==============================================================================
TitleScene::TitleScene()
	: IScene()				// 基底クラスのコンストラクタ
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleSceneのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
TitleScene::~TitleScene()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void TitleScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// BGMを鳴らす
	//auto _se = SoundManager::GetInstance();
	//_se->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_TEST, RepeatType::LOOP);
}

//==============================================================================
// 更新処理
//==============================================================================
void TitleScene::Update()
{
	auto _input = Input::GetInstance();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		ChangeScene(SCENE::EXIT);
	}

	// シーン遷移
	if (IsCanUpdate())
	{
		// タイマーの更新
		m_timer->Update();

		// UIの更新
		m_ui->Update();

		// 何か入力があればタイマーを再スタート
		if (m_ui->IsAnything())
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

		// スペースを押したら遷移する
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			m_ui->GetSelection() == UI_Title::Start ? ChangeScene(SCENE::SELECT) : ChangeScene(SCENE::EXIT);
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

//==============================================================================
// 描画処理
//==============================================================================
void TitleScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// 空の描画
	m_sky->Draw(_context, *_states, _view, _projection);

	// トリの描画
	m_birdTitle->Draw(_context, *_states, _view, _projection);

	// 氷山の描画
	m_iceberg->Draw(_context, *_states, _view, _projection);

	// 孤島の描画
	m_island->Draw(_context, *_states, _view, _projection);

	// 水の描画
	m_water->Draw(_view, _projection);

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

//==============================================================================
// 終了処理
//==============================================================================
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
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
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
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
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

//==============================================================================
// デバッグ描画
//==============================================================================
void TitleScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 },  Colors::DarkGreen, L"TitleScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", m_timer->GetCount());
}