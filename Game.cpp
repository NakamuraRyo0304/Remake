/*
 *	@File	Game.cpp
 *	@Brief	既存の改造版。
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game.h"

// TODO: ウィンドウタイトルの設定
const wchar_t* Game::TITLE = L"アデリー探検記";
const int Game::SCREEN_W = 1280;
const int Game::SCREEN_H = 720;
const XMVECTORF32 SCREEN_COLOR = Colors::CornflowerBlue;

using Microsoft::WRL::ComPtr;

// コンストラクタ
Game::Game() noexcept(false)
{
    // リソースを作成
    CreateDeviceDependentResources();
}

// 初期化
void Game::Initialize(HWND window, int width, int height)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    pDR->SetWindow(window, width, height);

    pDR->CreateDeviceResources();
    CreateDeviceDependentResources();

    pDR->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // タイマーの更新
    DX::StepTimer& timer = DX::StepTimer::GetInstance();
    timer.ResetElapsedTime();
    timer.SetFixedTimeStep(true);
    timer.SetTargetElapsedSeconds(1.0 / 60.0);

    // シーンの作成
    m_gameMain = std::make_unique<GameMain>();
    m_gameMain->CreateWDResources(width, height);
    m_gameMain->Initialize();
}

// 毎フレームの更新
void Game::Tick()
{
    // インスタンスの取得
    DX::StepTimer& timer = DX::StepTimer::GetInstance();
    auto input = Input::GetInstance();
    auto sound = SoundManager::GetInstance();

    // システムの更新
    timer.Tick([&]() { Update(input, sound); });

    // 描画処理
    Draw();
}


// システムの更新
void Game::Update(Input* input, SoundManager* sound)
{
    input->Update();
    sound->Update();
    m_gameMain->Update();
}


// 描画
void Game::Draw()
{
    DX::StepTimer& timer = DX::StepTimer::GetInstance();

    // 最初のUpdateの前に何かをレンダリングしようとしない
    if (timer.GetFrameCount() == 0) return;

    Clear();

    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    // ゲームの描画
    m_gameMain->Draw();

    // フレーム確認
    pDR->Present();
}


// バックバッファをリセット
void Game::Clear()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    // ビューの初期化
    auto context = pDR->GetD3DDeviceContext();
    auto rtv = pDR->GetRenderTargetView();
    auto dsv = pDR->GetDepthStencilView();

    // 色の変更・奥行のリセット・描画先の設定
    context->ClearRenderTargetView(rtv, SCREEN_COLOR);
    context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0U);
    context->OMSetRenderTargets(1, &rtv, dsv);

    // ビューポートの設定
    auto vp = pDR->GetScreenViewport();
    context->RSSetViewports(1, &vp);
}

#pragma region Message Handlers
void Game::OnActivated()
{
    // ウィンドウがアクティブである
}

void Game::OnDeactivated()
{
    // バックグラウンド中
}

void Game::OnSuspending()
{
    // 最小化中
}

void Game::OnResuming()
{
    DX::StepTimer& timer = DX::StepTimer::GetInstance();
    timer.ResetElapsedTime();
}

void Game::OnWindowMoved()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    auto rect = pDR->GetOutputSize();
    pDR->WindowSizeChanged(rect.right, rect.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    if (not pDR->WindowSizeChanged(width, height)) return;

    CreateWindowSizeDependentResources();

}


// 画面サイズを設定
void Game::GetDefaultSize(int& width, int& height) const
{
    width  = Game::SCREEN_W;
    height = Game::SCREEN_H;
}
#pragma endregion

#pragma region Direct3D Resources

// デバイス依存のリソースの初期化
void Game::CreateDeviceDependentResources()
{
    DX::DeviceResources::GetInstance();
    DX::StepTimer::GetInstance();
    Input::GetInstance();
}


// 画面依存のリソースの初期化
void Game::CreateWindowSizeDependentResources()
{
}

// デバイスが壊れた時の特殊処理
void Game::OnDeviceLost()
{
    m_gameMain.reset();
}

// デバイスが初期状態になった時全てを初期化
void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
