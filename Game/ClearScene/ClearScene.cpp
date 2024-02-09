/*
 *  @File   ClearScene.cpp
 *  @Brief  クリアシーン。
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// システム
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "ClearScene.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector2 ClearScene::PLAY_SC_OFFSET = { 50.0f, 50.0f };	// オフセット

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
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene(SCENE::TITLE);
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void ClearScene::Draw()
{
	auto _states = GetSystemManager()->GetCommonStates();

	// 画像のレクトを作成
	RECT_U _rect = RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));

	// 画面の拡大率
	SimpleMath::Vector2 _rate = GetWindowSize() / GetFullHDSize();

	// プレイシーンのスクショを描画
	m_sprite->DrawTexture(L"PlayPic",
		// 座標
		PLAY_SC_OFFSET * _rate,
		// 色 拡大率
		SimpleMath::Vector4(1, 1, 1, 0.5f), SimpleMath::Vector2::One * 0.5f * _rate,
		// 中心位置	画面サイズ
		SimpleMath::Vector2::Zero, _rect);

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
	m_sprite.reset();
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
void ClearScene::CreateWDResources()
{
	// スプライト描画の作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();

}

//==============================================================================
// シーン内の変数初期化関数
//==============================================================================
void ClearScene::SetSceneValues()
{
	// スプライトの設定
	m_sprite->AddTextureData(L"PlayPic", L"Resources/Textures/ScreenShot/image.dds");
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
