/*
 *	@File	ImageShot.cpp
 *	@Brief	�X�N���[���V���b�g���쐬�擾����N���X
 *	@Date	2024-02-08
 *  @Author	NakamuraRyo
 */

#include "pch.h"
#include "ScreenGrab.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "ImageShot.h"

 // �R���X�g���N�^
ImageShot::ImageShot()
{
    m_sprite = std::make_unique<DrawSprite>();
    m_sprite->MakeSpriteBatch();
}

// �f�X�g���N�^
ImageShot::~ImageShot()
{
    // �o�b�N�o�b�t�@�������[�X����
    ReleaseBackBuffer();
}

// �X�N���[���V���b�g���B�e���Ďw�肳�ꂽ�p�X�ɕۑ�����
HRESULT ImageShot::TakePic(const wchar_t* fileName, const wchar_t* copy)
{
    auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto swapChain = DX::DeviceResources::GetInstance()->GetSwapChain();

    // �o�b�N�o�b�t�@���擾
    HRESULT hr = S_OK;

    // �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɃR�s�[����
    hr = swapChain->Present(0, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    // �X���b�v�`�F�[������o�b�N�o�b�t�@���擾
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        return hr;
    }

    // �u�ԓI�Ƀf�[�^��ǉ�����
    m_sprite->Clear();
    m_sprite->AddTextureData(L"image", fileName);

    // �X�N���[���V���b�g��ۑ�����
    hr = SaveDDSTextureToFile(context, backBuffer.Get(), fileName);

    // �R�s�[���Ȃ��Ȃ炻�̂܂܃n���h����Ԃ�
    if (copy == nullptr) return hr;

    // �ۑ����ꂽ�摜���w�肵���p�X�ɃR�s�[����
    if (!CopyFile(fileName, copy, FALSE))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

// �X�N�V����`�悷��
void ImageShot::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate)
{
    m_sprite->DrawTexture(L"image", pos, SimpleMath::Vector4::One, rate, { 0,0 });
}

// �o�b�N�o�b�t�@���擾����
HRESULT ImageShot::GetBackBuffer()
{
    auto device = DX::DeviceResources::GetInstance()->GetD3DDevice();
    HRESULT hr = S_OK;
    if (!device)
    {
        return E_POINTER;
    }

    m_backBuffer = DX::DeviceResources::GetInstance()->GetRenderTarget();
    return hr;
}

// �o�b�N�o�b�t�@���������
void ImageShot::ReleaseBackBuffer()
{
    m_backBuffer.Reset();
}
