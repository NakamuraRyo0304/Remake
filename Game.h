/*
 *	@File	Game.h
 *	@Brief	既存の改造版。
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef GAME
#define GAME

#include "DeviceResources.h"
#include "StepTimer.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/SystemDatas/SoundManager/SoundManager.h"
#include "Libraries/SystemDatas/XController/XController.h"
#include "Game/GameMain.h"

class Game final : public DX::IDeviceNotify
{
public:

    const static wchar_t* TITLE;    // ゲームタイトル
    const static int SCREEN_W;      // 画面サイズ
    const static int SCREEN_H;

public:
    Game() noexcept(false);

    // 初期化
    void Initialize(HWND window, int width, int height);

    // ゲームループ
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // メッセージ
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);

    // プロパティ
    void GetDefaultSize( int& width, int& height ) const;

private:

    void Update(Input* input, SoundManager* sound, XController* xcon);
    void Draw();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // シーン
    std::unique_ptr<GameMain> m_gameMain;
};

#endif // GAME