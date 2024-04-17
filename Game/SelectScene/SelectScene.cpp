/*
 *	@File	SelectScene.cpp
 *	@Brief	セレクトシーン。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"											// プリコンパイル済みヘッダー
#include "Game/Cameras/AdminCamera/AdminCamera.h"			// 統合カメラ
#include "Game/SelectScene/System/UI_Select/UI_Select.h"	// ユーザインターフェース

#include "Game/SelectScene/Objects/BG_Select/BG_Select.h"	// 背景

#include "Game/Common/BlockManager/BlockManager.h"			// ブロック管理クラス
#include "Game/Common/Water/Water.h"						// 海

#include "SelectScene.h"									// セレクトシーン

// エイリアス宣言
using KeyCode = Keyboard::Keys;				// キーコード
using CameraType = AdminCamera::Type;		// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;	// サウンドのタイプ

// コンストラクタ
SelectScene::SelectScene(const int& selection)
	:
	IScene(),						// 基底クラスのコンストラクタ
	m_stageSelection(selection)		// 選択番号
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectSceneのコンストラクタが呼ばれました。\n");
}

// デストラクタ
SelectScene::~SelectScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectSceneのデストラクタが呼ばれました。\n");
	Finalize();
}

// 初期化
void SelectScene::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();

	// ボリューム設定・音量再生開始(BGM・環境音)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,  0.7f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,  RepeatType::LOOP);
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_SE_WAVE2, 0.7f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE2, RepeatType::LOOP);
}

// 更新
void SelectScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// タイトルに戻る
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::TITLE);
	}

	// UIの更新
	m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{
		// カメラの切り替え処理
		ChangeAdminCamera();

		// シーンセレクト
		SelectNext();
	}

	// カメラの更新
	m_adminCamera->Update();

	// ステージの更新
	for (int i = 0; i < MAX_SAMPLE_NUM; i++)
	{
		m_stage[i]->Update();
	}
}

// 描画
void SelectScene::Draw()
{
	// レンダリング変数を取得
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// ブロックの描画
	for (int i = 0; i < MAX_SAMPLE_NUM; i++)
	{
		m_stage[i]->Draw(context, *states, view, projection);
	}

	// 水の描画
	m_water->Draw(view, projection);

	// 背景の描画
	m_backGround->Draw();

	// UIの描画
	m_ui->Draw();

	// デバッグ描画
#if _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	//DebugDraw(*_states);
#endif
}

// 終了
void SelectScene::Finalize()
{
	m_adminCamera.reset();
	m_ui.reset();
	m_stage->reset();
	m_water.reset();
	m_backGround.reset();
}

// 画面、デバイス依存の初期化
void SelectScene::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI作成
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());

	// 水作成
	m_water = std::make_unique<Water>();

	// 背景作成
	m_backGround = std::make_unique<BG_Select>();

	// ブロックマネージャ
	m_stage[0] = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_stage[1] = std::make_unique<BlockManager>(L"Resources/Stages/sample2.json");
	m_stage[2] = std::make_unique<BlockManager>(L"Resources/Stages/sample3.json");
	m_stage[3] = std::make_unique<BlockManager>(L"Resources/Stages/sample4.json");
}

// シーン内の変数初期化関数
void SelectScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Select1_Floating);
	m_adminCamera->SetActive(true);

	// 選択中の番号を設定
	m_ui->SetSelectionNum(m_stageSelection);

	// 水の初期設定
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// 背景の初期設定
	m_backGround->Initialize();

	// ブロックの初期設定
	{
		// プレイモードに設定して初期化
		for (int i = 0; i < MAX_SAMPLE_NUM; i++)
		{
			m_stage[i]->SetPlay(true);
			m_stage[i]->Initialize();
		}

		// オフセットを設定
		m_stage[1]->SetOffset(SimpleMath::Vector3(10.5f, 0.0f, 0.0f));
		m_stage[2]->SetOffset(SimpleMath::Vector3(10.5f, 0.0f, -10.5f));
		m_stage[3]->SetOffset(SimpleMath::Vector3(0.0f, 0.0f, -10.5f));
	}
}

// デバッグ描画
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// 文字の描画
	string.DrawFormatString(states, { 0,0 },	Colors::DarkGreen, L"SelectScene");
	string.DrawFormatString(states, { 0,25 },	Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 },	Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 },	Colors::DarkGreen, L"Timer::%.2f", timer.GetTotalSeconds());
	string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"StageNum::%d", m_stageSelection);
}

// カメラの切り替え処理
void SelectScene::ChangeAdminCamera()
{
	if(m_stageSelection == EDITOR_NUM)
		m_adminCamera->SetType(CameraType::Select0_Floating);
	if (m_stageSelection == 1)
		m_adminCamera->SetType(CameraType::Select1_Floating);
	if (m_stageSelection == 2)
		m_adminCamera->SetType(CameraType::Select2_Floating);
	if (m_stageSelection == 3)
		m_adminCamera->SetType(CameraType::Select3_Floating);
	if (m_stageSelection == 4)
		m_adminCamera->SetType(CameraType::Select4_Floating);
}

// シーンを選択する
void SelectScene::SelectNext()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// ステージの選択
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		m_stageSelection++;
	}
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		m_stageSelection--;
	}

	// ループクランプ
	m_stageSelection = UserUtility::LoopClamp(m_stageSelection, EDITOR_NUM, MAX_SAMPLE_NUM);
	m_ui->SetSelectionNum(m_stageSelection);
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);

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
		if (m_stageSelection == 4)
			ChangeScene(SCENE::PLAY);
	}
}
