/*
 *	@File	GameMain.h
 *	@Brief	ゲームループを扱うクラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GAMEMAIN
#define GAMEMAIN

// 親シーンのインクルード
#include "Game/BaseScene/BaseScene.h"

 // 前方宣言
class Fade;

#ifdef _DEBUG
class Timer;
#endif

class GameMain
{
public:

    // コンストラクタ
    GameMain();
    // デストラクタ
    ~GameMain();
    // 初期化
    void Initialize();
    // 更新
    void Update();
    // 描画
    void Draw();
    // 終了
    void Finalize();
    // 画面依存、デバイス依存の初期化
    void CreateWDResources(const int& screenWidth, const int& screenHeight);
    // シーンの作成
    void CreateScene();
    // シーンの削除
    void DeleteScene();
    // ソフトを終了
    inline void ExitApp() { PostQuitMessage(0); }
    // シーンキャスタ    // CastSceneType<変換したいシーン型>(シーン)
    template<typename T>
    T* CastSceneType(std::unique_ptr<BaseScene>& scene)
    {
        return dynamic_cast<T*>(scene.get());
    }

private:

    // デフォルトのフェード速度
    const float DEFAULT_FADE_SPEED = 4.0f;
    // プレイシーンのフェード速度
    static const float PLAY_FADE_SPEED;
    // トランジションのパス
    static const wchar_t* FADE_TEXTURE_PATH;
    // トランジションの色
    static const DirectX::XMVECTORF32 FADE_COLOR;

private:

    // フェードオブジェクト
    std::unique_ptr<Fade> m_fade;
    // 現在処理するシーン
    std::unique_ptr<BaseScene> m_nowScene;
    // 未来のシーン、過去のシーン
    SCENE m_nextScene, m_prevScene;
    // スクリーンサイズ
    DirectX::SimpleMath::Vector2 m_screenSize;
    // ステージ番号/最大ステージ番号/コイン数
    int m_stageNumber, m_maxNumber, m_collectedCoin;
    // クリア時間
    float m_clearTime;

#ifdef _DEBUG
    // タイマー
    std::unique_ptr<Timer> m_timer;
#endif

};

#endif // GAMEMAIN