/*
 *	@File	GameMain.h
 *	@Brief	ゲームループを扱うクラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GAMEMAIN
#define GAMEMAIN

 // 前方宣言
class IScene;
class Fade;

// TODO: シーン１：シーンIDの追加
enum class SCENE : int
{
    NONE,       // ID無し

    TITLE,      // タイトルシーン
    SELECT,     // セレクトシーン
    PLAY,       // ゲームシーン
    EDIT,       // 制作シーン
    EXIT,       // 終了
};

class GameMain
{
private:

    // スクリーンサイズ
    DirectX::SimpleMath::Vector2 m_screenSize;

    // 未来のシーン、過去のシーン
    SCENE m_nextScene, m_prevScene;

    // 現在処理するシーン
    std::unique_ptr<IScene> m_nowScene;

    // フェードオブジェクト
    std::unique_ptr<Fade> m_fade;

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

    // ステージ番号
    int m_stageNumber;

public:
    GameMain();
    ~GameMain();

    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void Initialize();
    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void Update();
    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void Draw();
    /// <summary>
    /// 終了処理
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void Finalize();
    /// <summary>
    /// シーンの新規作成
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void CreateScene();
    /// <summary>
    /// シーンの削除
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    void DeleteScene();
    /// <summary>
    /// 画面依存、デバイス依存の初期化
    /// </summary>
    /// <param name="screenWidth">画面横幅</param>
    /// <param name="screenHeight">画面縦幅</param>
    /// <returns>なし</returns>
    void CreateWDResources(const int& screenWidth, const int& screenHeight);

    // シーンキャスタ    // 引数：T = 変換したい型名 / scene 今のシーン
    template<typename T>
    T* CastSceneType(std::unique_ptr<IScene>& scene)
    {
        return dynamic_cast<T*>(scene.get());
    }

    // ソフトを終了する
    inline void ExitApp() { PostQuitMessage(0); }
};

#endif // GAMEMAIN