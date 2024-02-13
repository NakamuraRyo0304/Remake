/*
 *  @File   ClearScene.cpp
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/ClearScene/System/MomentCanv/MomentCanv.h"
#include "Game/ClearScene/System/UI_Clear/UI_Clear.h"
#include "ClearScene.h"

//==============================================================================
// 定数の設定
//==============================================================================

//==============================================================================
// エイリアス宣言
//==============================================================================
using KeyCode = Keyboard::Keys;							// キーコード
using RepeatType = SoundManager::SE_MODE;				// サウンドのタイプ
using MouseClick = Mouse::ButtonStateTracker;			// マウスのクリック
using Selection = UI_Clear::SELECT;						// 次の選択

//==============================================================================
// コンストラクタ
//==============================================================================
ClearScene::ClearScene(float time, int coins, int stage, int max)
	: IScene()						// 基底クラスのコンストラクタ
	, m_clearTime{ time }			// クリアタイム
	, m_collectedCoin{ coins }		// 集めたコイン数
	, m_stageNumber{ stage }		// ステージ番号
	, m_maxNumber{ max }			// 最大ステージ番号
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearSceneのコンストラクタが呼ばれました。\n");
}

//==============================================================================
// デストラクタ
//==============================================================================
ClearScene::~ClearScene()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void ClearScene::Initialize()
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
void ClearScene::Update()
{
	auto _input = Input::GetInstance();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// シーン遷移
	if (IsCanUpdate())
	{
		// モーメントキャンバスの更新
		m_momentCanv->Update();

		// UIの更新
		m_ui->Update();

		// 次の遷移を選択
		auto _selection = m_ui->GetSelecion();
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
		{
			UserUtility::Increment(&_selection);	// インクリメント
		}
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
		{
			UserUtility::Decrement(&_selection);	// デクリメント
		}
		_selection = UserUtility::LoopClamp(_selection, Selection::NEXT, Selection::STAGES);
		m_ui->SetSelection(_selection);

		// 次の遷移を決定
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			switch (m_ui->GetSelecion())
			{
			case Selection::NEXT:
				m_stageNumber++;
				m_stageNumber = UserUtility::LoopClamp(m_stageNumber, 1, m_maxNumber);
				ChangeScene(SCENE::PLAY);
				break;
			case Selection::RESTART:
				ChangeScene(SCENE::PLAY);
				break;
			case Selection::STAGES:
				ChangeScene(SCENE::SELECT);
			default:
				break;
			}
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void ClearScene::Draw()
{
	// レンダリング変数を取得
	auto _states = GetSystemManager()->GetCommonStates();

	// モーメントキャンバスのレクトと拡大率、中心位置
	RECT_U _rectMC =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 _originMC = GetFullHDSize() * 0.5f;

	// モーメントキャンバスの描画
	m_momentCanv->Draw(SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, _originMC, _rectMC);

	// UIの描画
	m_ui->Draw();

	// デバッグ描画
#ifdef _DEBUG
	DebugDraw(*_states);
#endif
}

//==============================================================================
// 終了処理
//==============================================================================
void ClearScene::Finalize()
{
	m_momentCanv.reset();
	m_ui.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void ClearScene::CreateWDResources()
{
	// モーメントキャンバスの作成
	m_momentCanv = std::make_unique<MomentCanv>(GetWindowSize() / GetFullHDSize());

	// UIの作成
	m_ui = std::make_unique<UI_Clear>(GetWindowSize(), GetFullHDSize());
}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void ClearScene::SetSceneValues()
{
	// モーメントキャンバスの初期化
	m_momentCanv->Initialize();
}

//==============================================================================
// デバッグ描画
//==============================================================================
void ClearScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// 文字の描画
	_string.DrawFormatString(states, { 0,0 }, Colors::DarkGreen, L"ClearScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Time::%.2f",m_clearTime);
	_string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"Coin::%.d",m_collectedCoin);
	_string.DrawFormatString(states, { 0,125 }, Colors::DarkGreen, L"Stage::%.d", m_stageNumber);
}
