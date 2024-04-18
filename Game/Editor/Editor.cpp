/*
 *	@File	Editor.cpp
 *	@Brief	エディタ。
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"													// プリコンパイル済みヘッダー
#include "Game/Cameras/AdminCamera/AdminCamera.h"					// 統合カメラ
#include "Game/Editor/System/UI_Editor/UI_Editor.h"					// ユーザインターフェース

#include "Game/Common/BlockManager/BlockManager.h"					// ブロック管理クラス
#include "Game/Editor/System/EditorCollision/EditorCollision.h"		// エディタ当たり判定
#include "Game/Common/WorldMouse/WorldMouse.h"						// ３Ｄ変換後のマウスシステム
#include "Game/Common/CursorObject/CursorObject.h"					// ３Ｄ変換後のマウスオブジェクト
#include "Game/Editor/System/EditorGrids/EditorGrids.h"				// エディタ用グリッド線

#include "Editor.h"													// エディタシーン

// エイリアス宣言
using KeyCode = Keyboard::Keys;				// キーコード
using CameraType = AdminCamera::Type;		// カメラのタイプ
using RepeatType = SoundManager::SE_MODE;	// サウンドのタイプ
using BN = UI_Editor::BUTTON_NAME;			// ボタンの名前

// コンストラクタ
Editor::Editor()
	:
	BaseScene(),						// 基底クラスのコンストラクタ
	m_selectionID(ID::Obj_Flozen)		// 初期は氷床を設定
{
	Debug::DrawString::GetInstance().DebugLog(L"Editorのコンストラクタが呼ばれました。\n");
}

// デストラクタ
Editor::~Editor()
{
	Debug::DrawString::GetInstance().DebugLog(L"Editorのデストラクタが呼ばれました。\n");
	Finalize();
}

// 初期化
void Editor::Initialize()
{
	// 画面依存の初期化
	CreateWDResources();

	// 変数の初期化
	SetSceneValues();
}

// 更新
void Editor::Update()
{
	auto input = Input::GetInstance();

	// セレクトに戻る
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		ChangeScene(SCENE::SELECT);
	}

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
			m_blockManager->ReLoad(m_blockManager->GetStagePath());
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

// 描画
void Editor::Draw()
{
	// レンダリング変数を取得
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// カメラのマトリクスを取得
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// ブロックの描画
	m_blockManager->Draw(context, *states, view, projection);

	// ワールドマウスの描画関連を更新
	m_worldMouse->Draw(view, projection);

	// カーソルオブジェクトの描画
	m_cursorObject->Draw(context, *states, view, projection);

	// グリッドの描画
	for (int y = 0; y < 5; y++)
	{
		m_editorGrids->Draw(*states, SimpleMath::Matrix::Identity, view, projection, Colors::LightBlue,
			{ 4.5f, static_cast<float>(y) - 0.5f,4.5f });
	}
	m_editorGrids->Draw(*states, SimpleMath::Matrix::Identity, view, projection, Colors::Red,
		{ 4.5f, m_worldMouse->GetPosition().y - 0.5f,4.5f });

#if _DEBUG
	DebugDraw(*states);
#endif

	// UIの描画(最前面に描画)
	m_ui->Draw();
}

// 終了処理
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
	m_ui.reset();
	m_editorCollision.reset();
	m_worldMouse.reset();
	m_cursorObject.reset();
	m_editorGrids.reset();
}

// 画面、デバイス依存の初期化
void Editor::CreateWDResources()
{
	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// ブロックマネージャ作成
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/flat.json");
	m_blockManager->SetPlay(false);

	// UI作成
	m_ui = std::make_unique<UI_Editor>(GetWindowSize(), FULL_HD);

	// エディタコリジョン作成
	m_editorCollision = std::make_unique<EditorCollision>();

	// ワールドマウス作成
	m_worldMouse = std::make_unique<WorldMouse>();

	// カーソルオブジェクト作成
	m_cursorObject = std::make_unique<CursorObject>();

	// グリッド作成
	m_editorGrids = std::make_unique<EditorGrids>(10, 10);
}

// シーン内の変数初期化関数
void Editor::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);

	// IDの初期化
	m_selectionID = ID::Obj_Flozen;

	// ブロックの初期化
	m_blockManager->SetPlay(false);
	m_blockManager->Initialize();

	// エディタモードにする
	m_worldMouse->ToEditMode();

	// 座標を設定
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

// デバッグ描画
void Editor::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// 文字の描画
	string.DrawFormatString(states, { 0,0 },  Colors::Black, L"Editor");
	string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", timer.GetTotalSeconds());
	string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	string.DrawFormatString(states, { 0,125 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_editorCollision->GetPosition().x, m_editorCollision->GetPosition().y, m_editorCollision->GetPosition().z);
	string.DrawFormatString(states, { 0,150 }, Colors::Black, L"AddPosition::%.2f,%.2f",
		m_ui->GetAddPosition().x, m_ui->GetAddPosition().y);
}

// オブジェクトをセットする
void Editor::SetDrawObject()
{
	if (m_ui->IsClickButton(BN::Flozen_bn))	m_selectionID = ID::Obj_Flozen;	// 氷床
	if (m_ui->IsClickButton(BN::Cloud_bn))	m_selectionID = ID::Obj_Cloud;	// 雲
	if (m_ui->IsClickButton(BN::Coin_bn))	m_selectionID = ID::Obj_Coin;	// コイン
	if (m_ui->IsClickButton(BN::Air_bn))	m_selectionID = ID::Obj_Air;	// エア
	if (m_ui->IsClickButton(BN::Player_bn))	m_selectionID = ID::Obj_Player;	// プレイヤ
	if (m_ui->IsClickButton(BN::Goal_bn))	m_selectionID = ID::Obj_Goal;	// ゴール
	if (m_ui->IsClickButton(BN::Spike_bn))	m_selectionID = ID::Obj_Spike;	// 棘
	if (m_ui->IsClickButton(BN::Lift_bn))	m_selectionID = ID::Obj_Lift;	// リフト
}

// コリジョンの更新
void Editor::UpdateCollisions(ID id)
{
	for (auto& obj : m_blockManager->GetAirs())		// エアー（判定用ブロック）
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetFlozens())	// 氷床ブロック
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetClouds())	// 雲ギミック
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetCoins())	// コインオブジェクト
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetPlayers())	// プレイヤオブジェクト
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetGoals())	// ゴールポイント
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetSpikes())	// 棘エネミー
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetLifts())	// リフトブロック
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
}
