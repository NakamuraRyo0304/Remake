/*
 *	@File	SelectScene.cpp
 *	@Brief	セレクトシーン。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
 // ライブラリ
#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/XController/XController.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/SelectScene/System/UI_Select/UI_Select.h"
// オブジェクト

#include "SelectScene.h"

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
SelectScene::SelectScene()
	: IScene()				// 基底クラスのコンストラクタ
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectSceneのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
SelectScene::~SelectScene()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void SelectScene::Initialize()
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
void SelectScene::Update()
{
	auto _input = Input::GetInstance();
	//auto _se = SoundManager::GetInstance();
	//auto _xcon = XController::GetInstance();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UIの更新
	m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{
		// UI等の処理を行う

	}

	// カメラの更新
	m_adminCamera->Update();

}

//==============================================================================
// 描画処理
//==============================================================================
void SelectScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix  _projection = m_adminCamera->GetProjection();


	// UIの描画
	m_ui->Draw();

	// デバッグ描画
#ifdef _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif
}

//==============================================================================
// 終了処理
//==============================================================================
void SelectScene::Finalize()
{
	m_adminCamera.reset();
	m_ui.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void SelectScene::CreateWDResources()
{
	// デフォルトカメラ設定
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI作成
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void SelectScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);
}

//==============================================================================
// デバッグ描画
//==============================================================================
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 }, Colors::Black, L"SelectScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
}