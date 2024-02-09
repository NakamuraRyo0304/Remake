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

 //==============================================================================
 // �R���X�g���N�^
 //==============================================================================
ImageShot::ImageShot()
{
    m_sprite = std::make_unique<DrawSprite>();
    m_sprite->MakeSpriteBatch();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
ImageShot::~ImageShot()
{
    // �o�b�N�o�b�t�@�������[�X����
    ReleaseBackBuffer();
}

//==============================================================================
// �X�N���[���V���b�g���B�e���Ďw�肳�ꂽ�p�X�ɕۑ�����
//==============================================================================
HRESULT ImageShot::TakePic(const wchar_t* fileName)
{
    auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto _swapChain = DX::DeviceResources::GetInstance()->GetSwapChain();

    // �o�b�N�o�b�t�@���擾
    HRESULT _hr = S_OK;

    // �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɃR�s�[����
    _hr = _swapChain->Present(0, 0);
    if (FAILED(_hr))
    {
        return _hr;
    }

    // �X���b�v�`�F�[������o�b�N�o�b�t�@���擾
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _backBuffer;
    _hr = _swapChain->GetBuffer(0, IID_PPV_ARGS(_backBuffer.GetAddressOf()));
    if (FAILED(_hr))
    {
        return _hr;
    }

    // �X�N���[���V���b�g��ۑ�����t�@�C���p�X���쐬
    std::wstring _filePath = L"Resources/Textures/ScreenShot/";
    _filePath += fileName;

    // �u�ԓI�Ƀf�[�^��ǉ�����
    m_sprite->Clear();
    m_sprite->AddTextureData(L"image", _filePath.c_str());

    // �X�N���[���V���b�g��ۑ�����
    _hr = SaveDDSTextureToFile(_context, _backBuffer.Get(), _filePath.c_str());
    return _hr;
}

//==============================================================================
// �X�N�V����`�悷��
//==============================================================================
void ImageShot::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate)
{
    m_sprite->DrawTexture(L"image", pos, SimpleMath::Vector4::One, rate, { 0,0 });
}

//==============================================================================
// �o�b�N�o�b�t�@���擾����
//==============================================================================
HRESULT ImageShot::GetBackBuffer()
{
    auto _device = DX::DeviceResources::GetInstance()->GetD3DDevice();
    HRESULT _hr = S_OK;
    if (!_device)
    {
        return E_POINTER;
    }

    m_backBuffer = DX::DeviceResources::GetInstance()->GetRenderTarget();
    return _hr;
}

//==============================================================================
// �o�b�N�o�b�t�@���������
//==============================================================================
void ImageShot::ReleaseBackBuffer()
{
    m_backBuffer.Reset();
}
