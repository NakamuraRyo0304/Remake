/*
 *	@File	Editor.cpp
 *	@Brief	エディタ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Editor/System/UI_Editor/UI_Editor.h"
#include "Game/Editor/System/WorldMouse/WorldMouse.h"
// オブジェクト
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/Common/Blocks/Coin/Coin.h"

#include "Editor.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using CameraType = AdminCamera::Type;					// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ
using HitKinds = BlockManager::BlockKinds;				// ブロックの種類

//==============================================================================
// コンストラクタ
//==============================================================================
Editor::Editor()
	: IScene()				// 基底クラスのコンストラクタ
{
	Debug::DrawString::GetInstance().DebugLog(L"Editorのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
Editor::~Editor()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void Editor::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();
}

//==============================================================================
// 更新処理
//==============================================================================
void Editor::Update()
{
	auto _input = Input::GetInstance();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// UIの更新
	m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{

	}

	// カメラの更新
	m_adminCamera->Update();

	// ワールドマウスの更新
	m_worldMouse->Update();

	// ブロックの更新
	m_blockManager->Update();

	m_coin->SetPosition(m_worldMouse->GetPosition());
	m_coin->Update();

}

//==============================================================================
// 描画処理
//==============================================================================
void Editor::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix  _projection = m_adminCamera->GetProjection();

	// ブロックの描画
	m_blockManager->Draw(*_states, _view, _projection);

	// UIの描画
	m_ui->Draw();

	// ワールドマウスの描画
	m_worldMouse->Draw(_view, _projection);

	m_coin->Draw(*_states, _view, _projection);

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
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
	m_ui.reset();
	m_worldMouse.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void Editor::CreateWDResources()
{
	// デフォルトカメラ設定
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// ブロックマネージャ
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");

	// UI作成
	m_ui = std::make_unique<UI_Editor>(GetWindowSize(),GetFullHDSize());

	// ワールドマウスの作成
	m_worldMouse = std::make_unique<WorldMouse>(m_adminCamera->GetView(), m_adminCamera->GetProjection());

	m_coin = std::make_unique<Coin>(SimpleMath::Vector3::Zero);
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void Editor::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Select1_Floating);
	m_adminCamera->SetActive(true);
}

//==============================================================================
// デバッグ描画
//==============================================================================
void Editor::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 }, Colors::Yellow, L"Editor");
	_string.DrawFormatString(states, { 0,25 }, Colors::Yellow, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Yellow, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Yellow, L"Timer::%.2f", _time.GetTotalSeconds());
}