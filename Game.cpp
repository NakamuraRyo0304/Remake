/*
 *	@File	Game.cpp
 *	@Brief	�����̉����ŁB
 *	@Date	2023-11-03
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game.h"

// TODO: �E�B���h�E�^�C�g���̐ݒ�
const wchar_t* Game::TITLE = L"�A�f���[�T���L";
const int Game::SCREEN_W = 1280;
const int Game::SCREEN_H = 720;
const XMVECTORF32 SCREEN_COLOR = Colors::CornflowerBlue;

using Microsoft::WRL::ComPtr;

// �R���X�g���N�^
Game::Game() noexcept(false)
{
    // ���\�[�X���쐬
    CreateDeviceDependentResources();
}

// ������
void Game::Initialize(HWND window, int width, int height)
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    pDR->SetWindow(window, width, height);

    pDR->CreateDeviceResources();
    CreateDeviceDependentResources();

    pDR->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // �^�C�}�[�̍X�V
    DX::StepTimer& timer = DX::StepTimer::GetInstance();
    timer.ResetElapsedTime();
    timer.SetFixedTimeStep(true);
    timer.SetTargetElapsedSeconds(1.0 / 60.0);

    // �V�[���̍쐬
    m_gameMain = std::make_unique<GameMain>();
    m_gameMain->CreateWDResources(width, height);
    m_gameMain->Initialize();
}

// ���t���[���̍X�V
void Game::Tick()
{
    // �C���X�^���X�̎擾
    DX::StepTimer& timer = DX::StepTimer::GetInstance();
    auto input = Input::GetInstance();
    auto sound = SoundManager::GetInstance();

    // �V�X�e���̍X�V
    timer.Tick([&]() { Update(input, sound); });

    // �`�揈��
    Draw();
}


// �V�X�e���̍X�V
void Game::Update(Input* input, SoundManager* sound)
{
    input->Update();
    sound->Update();
    m_gameMain->Update();
}


// �`��
void Game::Draw()
{
    DX::StepTimer& timer = DX::StepTimer::GetInstance();

    // �ŏ���Update�̑O�ɉ����������_�����O���悤�Ƃ��Ȃ�
    if (timer.GetFrameCount() == 0) return;

    Clear();

    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    // �Q�[���̕`��
    m_gameMain->Draw();

    // �t���[���m�F
    pDR->Present();
}


// �o�b�N�o�b�t�@�����Z�b�g
void Game::Clear()
{
    DX::DeviceResources* pDR = DX::DeviceResources::GetInstance();

    // �r���[�̏�����
    auto context = pDR->GetD3DDeviceContext();
    auto rtv = pDR->GetRenderTargetView();
    auto dsv = pDR->GetDepthStencilView();

    // �F�̕ύX�E���s�̃��Z�b�g�E�`���̐ݒ�
    context->ClearRenderTargetView(rtv, SCREEN_COLOR);
    context->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0U);
    context->OMSetRenderTargets(1, &rtv, dsv);

    // �r���[�|�[�g�̐ݒ�
    auto vp = pDR->GetScreenViewport();
    context->RSSetViewports(1, &vp);
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


// ��ʃT�C�Y��ݒ�
void Game::GetDefaultSize(int& width, int& height) const
{
    width  = Game::SCREEN_W;
    height = Game::SCREEN_H;
}
#pragma endregion

#pragma region Direct3D Resources

// �f�o�C�X�ˑ��̃��\�[�X�̏�����
void Game::CreateDeviceDependentResources()
{
    DX::DeviceResources::GetInstance();
    DX::StepTimer::GetInstance();
    Input::GetInstance();
}


// ��ʈˑ��̃��\�[�X�̏�����
void Game::CreateWindowSizeDependentResources()
{
}

// �f�o�C�X����ꂽ���̓��ꏈ��
void Game::OnDeviceLost()
{
    m_gameMain.reset();
}

// �f�o�C�X��������ԂɂȂ������S�Ă�������
void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
