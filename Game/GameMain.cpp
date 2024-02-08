/*
 *	@File	GameMain.cpp
 *	@Brief	ゲームループを扱うクラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "GameMain.h"
#include "Libraries/SystemDatas/ScreenEffects/Fade/Fade.h"
#include "Libraries/UserUtility.h"

//==============================================================================
// 定数の設定
//==============================================================================
const wchar_t* GameMain::FADE_TEXTURE_PATH = L"Resources/Textures/Transitions/Rule_Haze.png";
const XMVECTORF32 GameMain::FADE_COLOR = Colors::White;
const float GameMain::PLAY_FADE_SPEED = 2.0f;

//==============================================================================
// シーンのインクルード
//==============================================================================
#include "TitleScene/TitleScene.h"
#include "SelectScene/SelectScene.h"
#include "Editor/Editor.h"
#include "PlayScene/PlayScene.h"
#include "ClearScene/ClearScene.h"

//==============================================================================
// コンストラクタ
//==============================================================================
GameMain::GameMain()
	: m_nextScene{ SCENE::TITLE }		// 次回のシーン
	, m_prevScene{ SCENE::NONE }		// 前回のシーン
	, m_nowScene{ nullptr }				// 今のシーンポインタ
	, m_screenSize{}					// スクリーンサイズ
	, m_stageNumber{ 1 }				// ステージ番号
{
}

//==============================================================================
// デストラクタ
//==============================================================================
GameMain::~GameMain()
{
	Finalize();
}

//==============================================================================
// 初期化処理
//==============================================================================
void GameMain::Initialize()
{
	// シーン作成
	CreateScene();

	// フェードイン
	m_fade->SetFadeIn();
}

//==============================================================================
// 更新処理
//==============================================================================
void GameMain::Update()
{
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

//==============================================================================
// 描画処理
//==============================================================================
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

//==============================================================================
// 終了処理
//==============================================================================
void GameMain::Finalize()
{
	m_nowScene.reset();
	m_fade.reset();
}

//==============================================================================
// シーン作成
//==============================================================================
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
			m_nowScene = std::make_unique<SelectScene>();

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
			m_nowScene = std::make_unique<ClearScene>();

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

	// 作成したシーンを初期化
	m_nowScene->SetWindowSize(m_screenSize);
	m_nowScene->Initialize();

	// フェードイン
	m_fade->SetFadeIn();

	// 次へのシーン情報を初期化
	m_nextScene = SCENE::NONE;
}

//==============================================================================
// シーンの削除
//==============================================================================
void GameMain::DeleteScene()
{
	// シーンが作成されていなければ処理しない
	if (not m_nowScene) return;


	//==============================================================================
	// シーン間の値受け渡しはここで行う
	//==============================================================================

	// 次のシーン：ゲームシーン / 処理：セレクトシーンからステージ番号を取得する
	if (m_nextScene == SCENE::PLAY && m_prevScene == SCENE::SELECT)
	{
		m_stageNumber = CastSceneType<SelectScene>(m_nowScene)->GetSelectedNumber();
	}



	// 現シーンの終了処理
	if (m_fade->GetFadeValue() >= m_fade->GetMaxValue())
	{
		// 現シーンの完全削除
		m_nowScene->Finalize();
		m_nowScene.reset();
		m_prevScene = m_nextScene;
	}
	else
	{
		m_fade->SetFadeOut();
	}
}

//==============================================================================
// 画面、デバイス依存の初期化
//==============================================================================
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