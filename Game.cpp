/*
 *	@File	Game.cpp
 *	@Brief	�����̉����ŁB
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game.h"

// TODO: �E�B���h�E�^�C�g���̐ݒ�
const wchar_t* Game::TITLE = L"SkyFallRemake";
const int Game::SCREEN_W = 1280;
const int Game::SCREEN_H = 720;
const XMVECTORF32 SCREEN_COLOR = Colors::CornflowerBlue;

using Microsoft::WRL::ComPtr;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Game::Game() noexcept(false)
{
    // ���\�[�X���쐬
    CreateDeviceDependentResources();
}

//==============================================================================
// ������
//==============================================================================
void Game::Initialize(HWND window, int width, int height)
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    _pDR->SetWindow(window, width, height);

    _pDR->CreateDeviceResources();
    CreateDeviceDependentResources();

    _pDR->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // �^�C�}�[�̍X�V
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();
    _stepTimer.ResetElapsedTime();
    _stepTimer.SetFixedTimeStep(true);
    _stepTimer.SetTargetElapsedSeconds(1.0 / 60.0);

    // �V�[���̍쐬
    m_gameMain = std::make_unique<GameMain>();
    m_gameMain->CreateWDResources(width, height);
    m_gameMain->Initialize();
}

//==============================================================================
// ���t���[���̍X�V
//==============================================================================
void Game::Tick()
{
    // �C���X�^���X�̎擾
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();
    auto _input = Input::GetInstance();
    auto _sound = SoundManager::GetInstance();
    auto _xCon = XController::GetInstance();

    // �V�X�e���̍X�V
    _stepTimer.Tick([&]() { Update(_input, _sound, _xCon); });

    // �`�揈��
    Draw();
}

//==============================================================================
// �V�X�e���̍X�V
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
// �`��
//==============================================================================
void Game::Draw()
{
    DX::StepTimer& _stepTimer = DX::StepTimer::GetInstance();

    // �ŏ���Update�̑O�ɉ����������_�����O���悤�Ƃ��Ȃ�
    if (_stepTimer.GetFrameCount() == 0) return;

    Clear();

    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    // �Q�[���̕`��
    m_gameMain->Draw();

    // �t���[���m�F
    _pDR->Present();
}

//==============================================================================
// �o�b�N�o�b�t�@�����Z�b�g
//==============================================================================
void Game::Clear()
{
    DX::DeviceResources* _pDR = DX::DeviceResources::GetInstance();

    // �r���[�̏�����
    auto _context = _pDR->GetD3DDeviceContext();
    auto _rtv = _pDR->GetRenderTargetView();
    auto _dsv = _pDR->GetDepthStencilView();

    // �F�̕ύX�E���s�̃��Z�b�g�E�`���̐ݒ�
    _context->ClearRenderTargetView(_rtv, SCREEN_COLOR);
    _context->ClearDepthStencilView(_dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0U);
    _context->OMSetRenderTargets(1, &_rtv, _dsv);

    // �r���[�|�[�g�̐ݒ�
    auto _viewport = _pDR->GetScreenViewport();
    _context->RSSetViewports(1, &_viewport);
}

#pragma region Message Handlers
void Game::OnActivated()
{
    // �E�B���h�E���A�N�e�B�u�ł���
}

void Game::OnDeactivated()
{
    // �o�b�N�O���E���h��
}

void Game::OnSuspending()
{
    // �ŏ�����
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
// ��ʃT�C�Y��ݒ�
//==============================================================================
void Game::GetDefaultSize(int& width, int& height) const
{
    width  = Game::SCREEN_W;
    height = Game::SCREEN_H;
}
#pragma endregion

#pragma region Direct3D Resources
//==============================================================================
// �f�o�C�X�ˑ��̃��\�[�X�̏�����
//==============================================================================
void Game::CreateDeviceDependentResources()
{
    DX::DeviceResources::GetInstance();
    DX::StepTimer::GetInstance();
    Input::GetInstance();
}

//==============================================================================
// ��ʈˑ��̃��\�[�X�̏�����
//==============================================================================
void Game::CreateWindowSizeDependentResources()
{
}

//==============================================================================
// �f�o�C�X����ꂽ���̓��ꏈ��
//==============================================================================
void Game::OnDeviceLost()
{
    m_gameMain.reset();
}

//==============================================================================
// �f�o�C�X��������ԂɂȂ������S�Ă�������
//==============================================================================
void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
