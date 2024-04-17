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

 // コンストラクタ
ImageShot::ImageShot()
{
    m_sprite = std::make_unique<DrawSprite>();
    m_sprite->MakeSpriteBatch();
}

// デストラクタ
ImageShot::~ImageShot()
{
    // バックバッファをリリースする
    ReleaseBackBuffer();
}

// スクリーンショットを撮影して指定されたパスに保存する
HRESULT ImageShot::TakePic(const wchar_t* fileName, const wchar_t* copy)
{
    auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto swapChain = DX::DeviceResources::GetInstance()->GetSwapChain();

    // バックバッファを取得
    HRESULT hr = S_OK;

    // バックバッファをフロントバッファにコピーする
    hr = swapChain->Present(0, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    // スワップチェーンからバックバッファを取得
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
    if (FAILED(hr))
    {
        return hr;
    }

    // 瞬間的にデータを追加する
    m_sprite->Clear();
    m_sprite->AddTextureData(L"image", fileName);

    // スクリーンショットを保存する
    hr = SaveDDSTextureToFile(context, backBuffer.Get(), fileName);

    // コピーしないならそのままハンドルを返す
    if (copy == nullptr) return hr;

    // 保存された画像を指定したパスにコピーする
    if (!CopyFile(fileName, copy, FALSE))
    {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
}

// スクショを描画する
void ImageShot::Draw(SimpleMath::Vector2 pos, SimpleMath::Vector2 rate)
{
    m_sprite->DrawTexture(L"image", pos, SimpleMath::Vector4::One, rate, { 0,0 });
}

// バックバッファを取得する
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

// バックバッファを解放する
void ImageShot::ReleaseBackBuffer()
{
    m_backBuffer.Reset();
}
