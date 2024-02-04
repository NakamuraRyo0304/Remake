/*
 *	@File	PlayScene.cpp
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/System/StageCollision/StageCollision.h"
//#include "Game/PlayScene/System/UI_Title/UI_Title.h"
// オブジェクト
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
#include "Game/PlayScene/Objects/Player/Player.h"
#include "Game/Common/CursorObject/CursorObject.h"
#include "PlayScene.h"

//==============================================================================
// 定数の設定
//==============================================================================


//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using CameraType = AdminCamera::Type;					// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ
using MouseClick = Mouse::ButtonStateTracker;			// マウスのクリック

//==============================================================================
// コンストラクタ
//==============================================================================
PlayScene::PlayScene(const int& number)
	: IScene()					// 基底クラスのコンストラクタ
	, m_stageNumber{ number }	// ステージ番号
{
	Debug::DrawString::GetInstance().DebugLog(L"PlaySceneのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
PlayScene::~PlayScene()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void PlayScene::Initialize()
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
void PlayScene::Update()
{
	auto _input = Input::GetInstance();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// シーン遷移
	if (IsCanUpdate())
	{
		// 追跡パスを追加
		if (_input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			SimpleMath::Vector3 _followPath = m_worldMouse->GetPosition();
			_followPath.y = m_player->GetPosition().y;
			m_player->PushBackFollowPath(_followPath);
		}

		// ゴールしたらシーン遷移 仮でセレクトに
		if (m_blockManager->IsArrived())
		{
			m_adminCamera->SetEasing(true);// 補間モードにする
			if (m_adminCamera->GetType() != CameraType::Select1_Floating)
			{
				m_adminCamera->SetType(CameraType::Select1_Floating);
			}
			ChangeScene(SCENE::SELECT);
		}

		// 死んだら再読み込み
		if (m_player->IsDeath())
		{
			ChangeScene(SCENE::PLAY);
		}
	}

#ifdef _DEBUG

	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
	{
		m_player->ResetGoalPosition();
		m_player->SetPosition({ 1.0f,0.5f,1.0f });
	}

#endif

	// カメラの更新
	m_adminCamera->Update();

	// ワールドマウスの更新
	m_worldMouse->Update();

	// カーソルオブジェクトを更新
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_cursorObject->Update();

	// スカイ球の更新(カメラを中心にスカイ球をセットする　描画切れを防ぐ)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// ブロックの更新
	m_blockManager->Update();

	// プレイヤーの更新
	m_player->Update();

	// 当たり判定の更新
	m_stageCollision->Update(m_player.get(), m_blockManager.get());
}

//==============================================================================
// 描画処理
//==============================================================================
void PlayScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ワールドマウスの描画
	m_worldMouse->Draw(_view, _projection);

	// カーソルオブジェクトの描画
	m_cursorObject->Draw(_context, *_states, _view, _projection);

	// 空の描画
	m_sky->Draw(_context, *_states, _view, _projection);

	// ブロックの描画
	m_blockManager->Draw(_context, *_states, _view, _projection);

	// プレイヤーの描画
	m_player->Draw(_context, *_states, _view, _projection);

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
void PlayScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_player.reset();
	m_worldMouse.reset();
	m_blockManager.reset();
	m_stageCollision.reset();
	m_cursorObject.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void PlayScene::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// スカイ球オブジェクト作成
	m_sky = std::make_unique<Sky_Play>();

	// プレイヤー作成
	m_player = std::make_unique<Player>();

	// ワールドマウス作成
	m_worldMouse = std::make_unique<WorldMouse>();

	// ブロックマネージャ作成
	m_blockManager = std::make_unique<BlockManager>(GetStagePath());

	// ステージコリジョン作成
	m_stageCollision = std::make_unique<StageCollision>();

	// カーソルオブジェクト作成
	m_cursorObject = std::make_unique<CursorObject>();
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void PlayScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetEasing(false);	// 補間を切る

	// ブロックの初期設定
	m_blockManager->SetPlay(true);
	m_blockManager->Initialize();

	// プレイヤーの座標を返す
	m_player->SetPosition(m_blockManager->GetPlayerPosition());

	// カーソルオブジェクトにワールドマウスの座標を設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

//==============================================================================
// デバッグ描画
//==============================================================================
void PlayScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"PlayScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"StageNum::%.d", m_stageNumber);
	_string.DrawFormatString(states, { 0,125 }, Colors::Black, L"PlayerPos::%.2f,%.2f,%.2f",
		m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	_string.DrawFormatString(states, { 0,150 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_worldMouse->GetPosition().x, m_worldMouse->GetPosition().y, m_worldMouse->GetPosition().z);
	_string.DrawFormatString(states, { 0,175 }, Colors::Black, L"SettingPath::%d", m_player->GetGoalPoints().size());
	_string.DrawFormatString(states, { 0,200 }, Colors::Black, L"HaveCoinNum::%d", m_player->GetCoinNum());
}

//==============================================================================
// ステージのパスを取得する
//==============================================================================
const wchar_t* PlayScene::GetStagePath()
{
	switch (m_stageNumber)
	{
	case 1:
		return L"Resources/Stages/sample1.json";
	case 2:
		return L"Resources/Stages/sample2.json";
	case 3:
		return L"Resources/Stages/sample3.json";


	default:
		return L"Resources/Stages/sample1.json";
	}
}
