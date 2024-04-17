/*
 *	@File	ImageShot.h
 *	@Brief	スクリーンショットを作成取得するクラス
 *	@Date	2024-02-08
 *  @Author	NakamuraRyo
 */

#pragma once
#ifndef IMAGESHOT
#define IMAGESHOT

class DrawSprite;
class ImageShot
{
public:

    // コンストラクタ
    ImageShot();
    // デストラクタ
    ~ImageShot();
    // スクリーンショットを撮影して指定されたファイルパスに保存する(パス、コピー先(無しでも可))
    HRESULT TakePic(const wchar_t* filePath, const wchar_t* copy = nullptr);
    // スクショを描画する
    void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate);

private:

    // バックバッファを取得する
    HRESULT GetBackBuffer();
    // バックバッファの解放
    void ReleaseBackBuffer();

private:

    // バックバッファ
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;
    // スプライト描画
    std::unique_ptr<DrawSprite> m_sprite;

};

#endif // SCREENSHOT_H
