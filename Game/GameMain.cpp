/*
 *	@File	GameMain.cpp
 *	@Brief	ゲームループを扱うクラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "GameMain.h"
#include "Libraries/SystemDatas/ScreenEffects/Fade/Fade.h"
#ifdef _DEBUG
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#endif

// 定数の設定
const wchar_t* GameMain::FADE_TEXTURE_PATH = L"Resources/Textures/Transitions/Rule_Haze.png";
const XMVECTORF32 GameMain::FADE_COLOR = Colors::LightSkyBlue;
const float GameMain::PLAY_FADE_SPEED = 2.0f;

// シーンのインクルード
#include "TitleScene/TitleScene.h"
#include "SelectScene/SelectScene.h"
#include "Editor/Editor.h"
#include "PlayScene/PlayScene.h"
#include "ClearScene/ClearScene.h"

// コンストラクタ
GameMain::GameMain()
	:
	m_nextScene(SCENE::TITLE),		// 次回のシーン
	m_prevScene(SCENE::NONE),		// 前回のシーン
	m_screenSize(),					// スクリーンサイズ
	m_stageNumber(1),				// ステージ番号
	m_clearTime(0.0f),				// クリア時間
	m_collectedCoin(0),				// 集めたコイン数
	m_maxNumber(999)				// 最大ステージ番号
{
	// カーソルを非表示
	ShowCursor(false);

	// タイマー計測開始
#ifdef _DEBUG
	m_timer = std::make_unique<Timer>(Timer::Mode::infinited);
	m_timer->Start();
	Debug::DrawString::GetInstance().DebugLog(L"タイマー計測開始！\n");
#endif

}

// デストラクタ
GameMain::~GameMain()
{
	Finalize();

	// カーソルを表示
	ShowCursor(true);
}

// 初期化
void GameMain::Initialize()
{
	// シーン作成
	CreateScene();

	// フェードイン
	m_fade->SetFadeIn();
}

// 更新
void GameMain::Update()
{
	// タイマー更新
#ifdef _DEBUG
	m_timer->Update();
#endif

	// フェードの更新
	m_fade->Update(FADE_COLOR);

	// 次のシーンが設定されていたらシーン切り替え
	if (m_nextScene != SCENE::NONE && m_fade->GetEndFlag())
	{
		// シーン削除
		DeleteScene();

		// シーン作成
		CreateScene();
	}

	// 実体があれば更新
	if (m_nowScene)
	{
		// シーンの更新処理
		m_nowScene->Update();

		// フェードの値をセット
		m_nowScene->SetFadeValue(m_fade->GetFadeValue());

		// フェードが終わっていたらシーンを切り替える
		if (m_fade->GetEndFlag())
		{
			m_nextScene = m_nowScene->GetNextScene();
		}
		else
		{
			m_nowScene->StopNextScene();
		}
	}
}

// 描画
void GameMain::Draw()
{
	// 実態があれば描画
	if (m_nowScene)
	{
		m_nowScene->Draw();
	}
	// フェードの描画
	m_fade->Draw();
}

// 終了
void GameMain::Finalize()
{
	m_nowScene.reset();
	m_fade.reset();

	// タイマー計測ストップ
#ifdef _DEBUG
	m_timer->Stop();
	Debug::DrawString::GetInstance().DebugLog(L"タイマー計測終了！\n");
	int minite = static_cast<int>(m_timer->GetCount() / 60.0f);
	int second = static_cast<int>(m_timer->GetCount()) % 60;
	std::wstring output = L"起動時間は" + std::to_wstring(minite) + L"分" + std::to_wstring(second) + L"秒\n";
	Debug::DrawString::GetInstance().DebugLog(output.c_str());
#endif
}

// シーン作成
void GameMain::CreateScene()
{
	// シーンが作成されていれば処理しない
	if (m_nowScene) return;

	// TODO:シーンはここから追加
	switch (m_nextScene)
	{
		case SCENE::TITLE:		// タイトルシーン
		{
			m_nowScene = std::make_unique<TitleScene>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::SELECT:		// セレクトシーン
		{
			m_nowScene = std::make_unique<SelectScene>(m_stageNumber);

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::EDIT:		// 制作シーン
		{
			m_nowScene = std::make_unique<Editor>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::PLAY:		// ゲームシーン
		{
			m_nowScene = std::make_unique<PlayScene>(m_stageNumber);

			m_fade->SetFadeSpeed(PLAY_FADE_SPEED);
			break;
		}
		case SCENE::CLEAR:		// クリアシーン
		{
			m_nowScene = std::make_unique<ClearScene>(
				m_clearTime, m_collectedCoin, m_stageNumber, m_maxNumber);

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::EXIT:		// ゲーム終了
		{
			if (m_fade->GetEndFlag()) { ExitApp(); }
			return;
		}
		default:
			break;
	}

	// 音を初期設定に戻す
	SoundManager::GetInstance()->InitAllSounds();

	// 作成したシーンを初期化
	m_nowScene->SetWindowSize(m_screenSize);
	m_nowScene->Initialize();

	// フェードイン
	m_fade->SetFadeIn();

	// 次へのシーン情報を初期化
	m_nextScene = SCENE::NONE;
}

// シーンの削除
void GameMain::DeleteScene()
{
	// シーンが作成されていなければ処理しない
	if (not m_nowScene) return;

	// シーン間の値受け渡しは　　<<ここから

	// セレクトシーン ----> プレイシーン
	// 処理：選択されたステージ番号を送信
	if (m_prevScene == SCENE::SELECT && m_nextScene == SCENE::PLAY)
	{
		m_stageNumber   = CastSceneType<SelectScene>(m_nowScene)->GetSelectedNumber();
		m_maxNumber     = CastSceneType<SelectScene>(m_nowScene)->GetMaxNumber();
	}
	// クリアシーン ----> プレイシーン
	// 処理：次のステージ番号を送信（最大になったら１に戻す）
	if (m_prevScene == SCENE::CLEAR && m_nextScene == SCENE::PLAY)
	{
		m_stageNumber   = CastSceneType<ClearScene>(m_nowScene)->GetStageNumber();
	}

	// プレイシーン ----> クリアシーン
	// 処理：ステージ番号、クリア時間、獲得コインを送信
	if (m_prevScene == SCENE::PLAY && m_nextScene == SCENE::CLEAR)
	{
		m_clearTime     = CastSceneType<PlayScene>(m_nowScene)->GetGameTimer();
		m_collectedCoin = CastSceneType<PlayScene>(m_nowScene)->GetCollectedCoin();
		m_stageNumber   = CastSceneType<PlayScene>(m_nowScene)->GetStageNumber();
	}

	// シーン間の値受け渡しは　　<<ここまで


	// 現シーンの終了処理
	if (m_fade->GetFadeValue() >= m_fade->GetMaxValue())
	{
		m_nowScene->Finalize();
		m_nowScene.reset();
		m_prevScene = m_nextScene;
	}
	else
	{
		m_fade->SetFadeOut();
	}
}

// 画面、デバイス依存の初期化
void GameMain::CreateWDResources(const int& screenWidth, const int& screenHeight)
{
	// スクリーンサイズの設定
	m_screenSize.x = static_cast<float>(screenWidth);
	m_screenSize.y = static_cast<float>(screenHeight);

	// フェードの設定
	m_fade = std::make_unique<Fade>(DEFAULT_FADE_SPEED);
	m_fade->SetRuleTexture(FADE_TEXTURE_PATH);
	m_fade->Initialize();
}