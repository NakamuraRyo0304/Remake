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
private:

    // バックバッファ
    Microsoft::WRL::ComPtr<ID3D11Texture2D> m_backBuffer;

    // スプライト描画
    std::unique_ptr<DrawSprite> m_sprite;

public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="引数無し"></param>
    /// <returns>なし</returns>
    ImageShot();
    ~ImageShot();

    /// <summary>
    /// スクリーンショットを撮影して指定されたファイルパスに保存する
    /// </summary>
    /// <param name="filePath">保存先のパス</param>
    /// <returns>なし</returns>
    HRESULT TakePic(const wchar_t* filePath);

    /// <summary>
    /// スクショを描画する
    /// </summary>
    /// <param name="pos">座標</param>
    /// <param name="rate">拡大率</param>
    /// <returns>なし</returns>
    void Draw(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate);

private:

    // バックバッファを取得する
    HRESULT GetBackBuffer();

    // バックバッファの解放
    void ReleaseBackBuffer();
};

#endif // SCREENSHOT_H
