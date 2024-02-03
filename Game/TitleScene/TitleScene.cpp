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
// オブジェクト
#include "Game/TitleScene/Objects/Sky_Title/Sky_Title.h"
#include "Game/TitleScene/Objects/Logo/Logo.h"
#include "Game/TitleScene/Objects/Bird_Title/Bird_Title.h"
#include "TitleScene.h"

//==============================================================================
// 定数の設定
//==============================================================================


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
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UIの更新
	m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{
		// スペースを押したら遷移する
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			m_adminCamera->SetType(CameraType::Title_OverHead);
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

	// ロゴの更新
	m_logo->Update();
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

	// ロゴの描画
	m_logo->Draw(_context, *_states, _view, _projection);

	// UIの表示
	m_ui->Draw();


	// デバッグ描画
#ifdef _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif
}

//==============================================================================
// 終了処理
//==============================================================================
void TitleScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_logo.reset();
	m_ui.reset();
	m_birdTitle.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void TitleScene::CreateWDResources()
{
	// デフォルトカメラ設定
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// スカイ球オブジェクト作成
	m_sky = std::make_unique<Sky_Title>();

	// ロゴオブジェクト作成
	m_logo = std::make_unique<Logo>();

	// UI作成
	m_ui = std::make_unique<UI_Title>(GetWindowSize(), GetFullHDSize());

	// トリオブジェクト作成
	m_birdTitle = std::make_unique<Bird_Title>();
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void TitleScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

}

//==============================================================================
// デバッグ描画
//==============================================================================
void TitleScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"TitleScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
}