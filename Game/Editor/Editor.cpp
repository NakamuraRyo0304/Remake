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
#include "Game/Editor/System/EditorCollision/EditorCollision.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Libraries/UserUtility.h"
// オブジェクト
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/Common/CursorObject/CursorObject.h"

#include "Editor.h"

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using CameraType = AdminCamera::Type;					// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ
using BN = UI_Editor::BUTTON_NAME;						// ボタンの名前

//==============================================================================
// コンストラクタ
//==============================================================================
Editor::Editor()
	: IScene()						// 基底クラスのコンストラクタ
	, m_selectionID{ ID::Obj_Flozen }	// 初期は砂を設定
{
	Debug::DrawString::GetInstance().DebugLog(L"Editorのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
Editor::~Editor()
{
	Finalize();
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
		if (m_ui->IsClickButton(BN::LoadFile))
		{
			m_blockManager->ReLoad();
			m_adminCamera->SetType(CameraType::Editor_Moving);
		}
		if (m_ui->IsClickButton(BN::WriteFile))
		{
			m_blockManager->OutputStage();
		}
	}

	// ブロックの更新
	m_blockManager->Update();

	// カメラの更新
	m_adminCamera->Update();

	// オブジェクトをセットする
	SetDrawObject();

	// ワールドマウスを更新
	m_worldMouse->Update();

	// ワールドマウスの座標をコリジョン・視覚化オブジェクトに設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_editorCollision->SetPosition(m_worldMouse->GetPosition());

	// カーソルオブジェクトを更新
	m_cursorObject->Update();

	// エディタコリジョンの更新
	UpdateCollisions(m_selectionID);
}

//==============================================================================
// 描画処理
//==============================================================================
void Editor::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ブロックの描画
	m_blockManager->Draw(_context, *_states, _view, _projection);

	// ワールドマウスの描画関連を更新
	m_worldMouse->Draw(_view, _projection);

	// カーソルオブジェクトの描画
	m_cursorObject->Draw(_context, *_states, _view, _projection);

	// デバッグ描画
#if _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif

	// UIの描画(最前面に描画)
	m_ui->Draw();
}

//==============================================================================
// 終了処理
//==============================================================================
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
	m_ui.reset();
	m_editorCollision.reset();
	m_worldMouse.reset();
	m_cursorObject.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void Editor::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// ブロックマネージャ作成
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_blockManager->SetPlay(false);

	// UI作成
	m_ui = std::make_unique<UI_Editor>(GetWindowSize(),GetFullHDSize());

	// エディタコリジョン作成
	m_editorCollision = std::make_unique<EditorCollision>();

	// ワールドマウス作成
	m_worldMouse = std::make_unique<WorldMouse>();

	// カーソルオブジェクト作成
	m_cursorObject = std::make_unique<CursorObject>();
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void Editor::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);

	// IDを砂に設定
	m_selectionID = ID::Obj_Flozen;

	// ブロックの初期化
	m_blockManager->Initialize();

	// エディタモードにする
	m_worldMouse->ToEditMode();

	// 座標を設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

//==============================================================================
// デバッグ描画
//==============================================================================
void Editor::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"Editor");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	_string.DrawFormatString(states, { 0,125 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_editorCollision->GetPosition().x, m_editorCollision->GetPosition().y, m_editorCollision->GetPosition().z);
	_string.DrawFormatString(states, { 0,150 }, Colors::Black, L"AddPosition::%.2f,%.2f",
		m_ui->GetAddPosition().x, m_ui->GetAddPosition().y);
}

//==============================================================================
// コリジョンの更新
//==============================================================================
void Editor::UpdateCollisions(ID id)
{
	//////////////////////////////////////////
	///            ※複文省略              ///
	//////////////////////////////////////////

	for (auto& obj : m_blockManager->GetAirBlock())		// エアオブジェクト
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetFlozenBlock())	// 砂ブロック
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetCloudBlock())	// 雲ギミック
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetCoinBlock())	// コインオブジェクト
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetPlayerBlock())	// プレイヤオブジェクト
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetGoalObject())	// ゴールポイント
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetSpikeEnemy())	// 棘エネミー
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
}

//==============================================================================
// オブジェクトをセットする
//==============================================================================
void Editor::SetDrawObject()
{
	if (m_ui->IsClickButton(BN::Flozen_bn))	m_selectionID = ID::Obj_Flozen;	// 砂
	if (m_ui->IsClickButton(BN::Cloud_bn))	m_selectionID = ID::Obj_Cloud;	// 雲
	if (m_ui->IsClickButton(BN::Coin_bn))	m_selectionID = ID::Obj_Coin;	// コイン
	if (m_ui->IsClickButton(BN::Air_bn))	m_selectionID = ID::Obj_Air;	// エア
	if (m_ui->IsClickButton(BN::Player_bn))	m_selectionID = ID::Obj_Player;	// プレイヤ
	if (m_ui->IsClickButton(BN::Goal_bn))	m_selectionID = ID::Obj_Goal;	// ゴール
	if (m_ui->IsClickButton(BN::Spike_bn))	m_selectionID = ID::Obj_Spike;	// 棘
}
