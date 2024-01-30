/*
 *	@File	PlayScene.cpp
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/Cameras/AdminCamera/AdminCamera.h"
//#include "Game/PlayScene/System/UI_Title/UI_Title.h"
// オブジェクト
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
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
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UIの更新
	//m_ui->Update();

	// シーン遷移
	if (IsCanUpdate())
	{

	}

	// カメラの更新
	m_adminCamera->Update();

	// スカイ球の更新(カメラを中心にスカイ球をセットする　描画切れを防ぐ)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

}

//==============================================================================
// 描画処理
//==============================================================================
void PlayScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();

	// カメラのマトリクスを取得
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix  _projection = m_adminCamera->GetProjection();

	// 空の描画
	m_sky->Draw(*_states, _view, _projection);




	// UIの表示
//	m_ui->Draw();


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
void PlayScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void PlayScene::CreateWDResources()
{
	// デフォルトカメラ設定
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// ゲームカメラ作成
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// スカイ球オブジェクト作成
	m_sky = std::make_unique<Sky_Play>();

}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void PlayScene::SetSceneValues()
{
	// カメラの初期設定-自動
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetEasing(false);	// 補間を切る


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
}