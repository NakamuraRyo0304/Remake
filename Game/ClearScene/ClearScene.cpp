/*
 *  @File   ClearScene.cpp
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Game/ClearScene/System/MomentCanv/MomentCanv.h"
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

//==============================================================================
// コンストラクタ
//==============================================================================
ClearScene::ClearScene()
	: IScene()						// 基底クラスのコンストラクタ
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
	auto _key = Keyboard::Get().GetState();

	// ソフト終了
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// シーン遷移
	if (IsCanUpdate())
	{
		// モーメントキャンバスの更新
		m_momentCanv->Update();

		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene(SCENE::SELECT);
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
	SimpleMath::Vector2 _rateMC = GetWindowSize() / GetFullHDSize();
	SimpleMath::Vector2 _originMC = GetWindowSize() * _rateMC * 0.5f;


	// モーメントキャンバスの描画
	m_momentCanv->Draw(_rateMC, SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, _originMC, _rectMC);

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
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void ClearScene::CreateWDResources()
{
	// モーメントキャンバスの作成
	m_momentCanv = std::make_unique<MomentCanv>();

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
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", _time.GetTotalSeconds());
}
