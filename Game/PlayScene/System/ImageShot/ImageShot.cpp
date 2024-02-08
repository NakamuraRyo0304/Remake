/*
 *	@File	ImageShot.cpp
 *	@Brief	スクリーンショットを作成取得するクラス
 *	@Date	2024-02-08
 *  @Author	NakamuraRyo
 */

#include "pch.h"
#include "ScreenGrab.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "ImageShot.h"

 //==============================================================================
 // コンストラクタ
 //==============================================================================
ImageShot::ImageShot()
{
    m_sprite = std::make_unique<DrawSprite>();
    m_sprite->MakeSpriteBatch();
}

//==============================================================================
// デストラクタ
//==============================================================================
ImageShot::~ImageShot()
{
    // バックバッファをリリースする
    ReleaseBackBuffer();
}

//==============================================================================
// スクリーンショットを撮影して指定されたパスに保存する
//==============================================================================
HRESULT ImageShot::TakePic(const wchar_t* fileName)
{
    auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto _swapChain = DX::DeviceResources::GetInstance()->GetSwapChain();

    // バックバッファを取得
    HRESULT _hr = S_OK;

    // スワップチェーンからバックバッファを取得
    Microsoft::WRL::ComPtr<ID3D11Texture2D> _backBuffer;
    _hr = _swapChain->GetBuffer(0, IID_PPV_ARGS(_backBuffer.GetAddressOf()));
    if (FAILED(_hr))
    {
        return _hr;
    }

    // スクリーンショットを保存するファイルパスを作成
    std::wstring _filePath = L"Resources/Textures/ScreenShot/";
    _filePath += fileName;

    // スクリーンショットを保存する
    _hr = SaveDDSTextureToFile(_context, _backBuffer.Get(), _filePath.c_str());
    if (FAILED(_hr))
    {
        return _hr;
    }

    // 瞬間的にデータを追加する
    m_sprite->Clear();
    m_sprite->AddTextureData(L"image", _filePath.c_str());

    return _hr;
}

//==============================================================================
// スクショを描画する
//==============================================================================
void ImageShot::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate)
{
    m_sprite->DrawTexture(L"image", pos, SimpleMath::Vector4::One, rate, { 0,0 });
}

//==============================================================================
// バックバッファを取得する
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
// バックバッファを解放する
//==============================================================================
void ImageShot::ReleaseBackBuffer()
{
    m_backBuffer.Reset();
}
