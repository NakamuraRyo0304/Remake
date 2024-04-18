/*
 *	@File	DepthStencil.h
 *	@Brief	深度ステンシル作成クラス。
 *	@Date	2023-11-24
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DEPTHSTENCIL
#define DEPTHSTENCIL

class DepthStencil
{
public:

    // デバイスを設定
    void SetDevice(_In_ ID3D11Device* device);
    // リソース（幅と高さ）のサイズを設定
    void SizeResources(size_t width, size_t height);
    // デバイスおよび関連するリソースを解放
    void ReleaseDevice() noexcept;
    // 指定されたRECT構造に基づいてウィンドウのサイズを設定
    void SetWindow(const RECT& rect);
    // テクスチャを取得
    ID3D11Texture2D* GetTexture2D() const noexcept { return m_texture2D.Get(); }
    // デプスステンシルビューを取得
    ID3D11DepthStencilView* GetDepthStencilView() const noexcept { return m_depthStencilView.Get(); }
    // フォーマットを取得
    DXGI_FORMAT GetFormat() const noexcept { return m_format; }

    // ムーブコンストラクタ
    DepthStencil(DepthStencil&&) = default;
    DepthStencil& operator= (DepthStencil&&) = default;

    // フォーマットを受け取るコンストラクタ
    explicit DepthStencil(DXGI_FORMAT format) noexcept;

    // 削除済みコピーコンストラクタ
    DepthStencil(DepthStencil const&) = delete;
    DepthStencil& operator= (DepthStencil const&) = delete;

private:

    // デバイス
    Microsoft::WRL::ComPtr<ID3D11Device>                m_device;
    // テクスチャ
    Microsoft::WRL::ComPtr<ID3D11Texture2D>             m_texture2D;
    // デプスステンシルビュー
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>      m_depthStencilView;
    // フォーマット
    DXGI_FORMAT                                         m_format;
    // 横幅
    size_t                                              m_width;
    // 縦幅
    size_t                                              m_height;

};

#endif // DEPTHSTENCIL