/*
 *	@File	Game.cpp
 *	@Brief	既存の改造版。
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game.h"

// TODO: ウィンドウタイトルの設定
const wchar_t* Game::TITLE = L"SkyFallRemake";
const int Game::SCREEN_W = 1280;
const int Game::SCREEN_H = 720;
const XMVECTORF32 SCREEN_COLOR = Colors::CornflowerBlue;

using Microsoft::WRL::ComPtr;

//==============================================================================
// コンストラクタ
//==============================================================================
Game::Game() noexcept(false)
{
    // リソースを作成
    CreateDeviceDependentResources();
}

//==============================================================================
// 初期化
//==============================================================================
void Game::Initialize(HWND window, int width, int height)
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    _pDR->SetWindow(window, width, height);

    _pDR->CreateDeviceResources();
    CreateDeviceDependentResources();

    _pDR->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // タイマーの更新
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();
    _stepTimer.ResetElapsedTime();
    _stepTimer.SetFixedTimeStep(true);
    _stepTimer.SetTargetElapsedSeconds(1.0 / 60.0);

    // シーンの作成
    m_gameMain = std::make_unique<GameMain>();
    m_gameMain->CreateWDResources(width, height);
    m_gameMain->Initialize();
}

//==============================================================================
// 毎フレームの更新
//==============================================================================
void Game::Tick()
{
    // インスタンスの取得
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();
    auto _input = Input::GetInstance();
    auto _sound = SoundManager::GetInstance();
    auto _xCon = XController::GetInstance();

    // システムの更新
    _stepTimer.Tick([&]() { Update(_input, _sound, _xCon); });

    // 描画処理
    Draw();
}

//==============================================================================
// システムの更新
//==============================================================================
void Game::Update(Input* input, SoundManager* sound, XController* xcon)
{
    input->Update();
    sound->Update();

    if (xcon != nullptr)
    {
        xcon->Update();
    }
    m_gameMain->Update();
}

//==============================================================================
// 描画
//==============================================================================
void Game::Draw()
{
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();

    // 最初のUpdateの前に何かをレンダリングしようとしない
    if (_stepTimer.GetFrameCount() == 0) return;

    Clear();

    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    // ゲームの描画
    m_gameMain->Draw();

    // フレーム確認
    _pDR->Present();
}

//==============================================================================
// バックバッファをリセット
//==============================================================================
void Game::Clear()
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    // ビューの初期化
    auto _context = _pDR->GetD3DDeviceContext();
    auto _rtv = _pDR->GetRenderTargetView();
    auto _dsv = _pDR->GetDepthStencilView();

    // 色の変更・奥行のリセット・描画先の設定
    _context->ClearRenderTargetView(_rtv, SCREEN_COLOR);
    _context->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0U);
    _context->OMSetRenderTargets(1, &_rtv, _dsv);

    // ビューポートの設定
    auto _viewport = _pDR->GetScreenViewport();
    _context->RSSetViewports(1, &_viewport);
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
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();
    _stepTimer.ResetElapsedTime();
}

void Game::OnWindowMoved()
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    auto _rect = _pDR->GetOutputSize();
    _pDR->WindowSizeChanged(_rect.right, _rect.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    if (not _pDR->WindowSizeChanged(width, height)) return;

    CreateWindowSizeDependentResources();

}

//==============================================================================
// 画面サイズを設定
//==============================================================================
void Game::GetDefaultSize(int& width, int& height) const
{
    width  = Game::SCREEN_W;
    height = Game::SCREEN_H;
}
#pragma endregion

#pragma region Direct3D Resources
//==============================================================================
// デバイス依存のリソースの初期化
//==============================================================================
void Game::CreateDeviceDependentResources()
{
    DX::DeviceResources::GetInstance();
    DX::StepTimer::GetInstance();
    Input::GetInstance();
}

//==============================================================================
// 画面依存のリソースの初期化
//==============================================================================
void Game::CreateWindowSizeDependentResources()
{
}

//==============================================================================
// デバイスが壊れた時の特殊処理
//==============================================================================
void Game::OnDeviceLost()
{
    m_gameMain.reset();
}

//==============================================================================
// デバイスが初期状態になった時全てを初期化
//==============================================================================
void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
