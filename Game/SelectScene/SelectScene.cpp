/*
 *	@File	SelectScene.cpp
 *	@Brief	セレクトシーン。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/SelectScene/System/UI_Select/UI_Select.h"
#include "Game/SelectScene/Objects/Sky_Select/Sky_Select.h"
// オブジェクト
#include "Game/Common/BlockManager/BlockManager.h"

#include "SelectScene.h"

//==============================================================================
// 定数の設定
//==============================================================================
const int SelectScene::MAX_SAMPLE_NUM = 3;		// サンプルステージ数

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
	, m_stageSelection{ 1 }	// ステージ１からスタート
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

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UIの更新
	m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{
		// ステージの選択
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
		{
			m_stageSelection++;
		}
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
		{
			m_stageSelection--;
		}

		// ループクランプ
		m_stageSelection = UserUtility::LoopClamp(m_stageSelection, EDITOR_NUM, MAX_SAMPLE_NUM);
		m_ui->SetSelectionNum(m_stageSelection);
	}

	// カメラの切り替え処理
	ChangeAdminCamera();

	// シーンセレクト
	SelectNext();

	// カメラの更新
	m_adminCamera->Update();

	// スカイ球の更新
	m_sky->Update();
	m_sky->SetPosition(m_adminCamera->GetPosition());

	// ブロックの更新
	m_blockManager->Update();
}

//==============================================================================
// 描画処理
//==============================================================================
void SelectScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ステージオブジェクトの描画
	m_sky->Draw(_context, *_states, _view, _projection);

	// ブロックの描画
	m_blockManager->Draw(_context, *_states, _view, _projection);

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
	m_sky.reset();
	m_blockManager.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void SelectScene::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI作成
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());

	// スカイ球作成
	m_sky = std::make_unique<Sky_Select>();

	// ブロックマネージャ
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_blockManager->SetPlay(true);
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void SelectScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

	// 選択中の番号を設定
	m_ui->SetSelectionNum(m_stageSelection);

	// ブロックの初期化
	m_blockManager->Initialize();
}

//==============================================================================
// デバッグ描画
//==============================================================================
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 }, Colors::Yellow, L"SelectScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Yellow, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Yellow, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Yellow, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Yellow, L"StageNum::%d", m_stageSelection);
}

//==============================================================================
// カメラの切り替え処理
//==============================================================================
void SelectScene::ChangeAdminCamera()
{
	if(m_stageSelection == EDITOR_NUM)
		m_adminCamera->SetType(CameraType::Title_FixedPoint);
	if (m_stageSelection == 1)
		m_adminCamera->SetType(CameraType::Select1_Floating);
	if (m_stageSelection == 2)
		m_adminCamera->SetType(CameraType::Select2_Floating);
	if (m_stageSelection == 3)
		m_adminCamera->SetType(CameraType::Select3_Floating);
}

//==============================================================================
// シーンを選択する
//==============================================================================
void SelectScene::SelectNext()
{
	auto _input = Input::GetInstance();

	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
	{
		// ステージを作る
		if (m_stageSelection == EDITOR_NUM)
			ChangeScene(SCENE::EDIT);

		// ステージをプレイする
		if (m_stageSelection == 1)
			ChangeScene(SCENE::PLAY);
		if (m_stageSelection == 2)
			ChangeScene(SCENE::PLAY);
		if (m_stageSelection == 3)
			ChangeScene(SCENE::PLAY);
	}
}
