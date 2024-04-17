/*
 *	@File	DrawString.h
 *	@Brief	デバッグ文字描画。
 *	@Date	2023-04-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWSTRING
#define DRAWSTRING

namespace Debug
{
	class DrawString
	{
	public:

		// インスタンスの作成＆取得
		static Debug::DrawString& GetInstance()
		{
			static DrawString instance(
				DX::DeviceResources::GetInstance()->GetD3DDevice(),
				DX::DeviceResources::GetInstance()->GetD3DDeviceContext()
			);

			return instance;
		}

	private:

		// コンストラクタ
		DrawString(ID3D11Device1* device, ID3D11DeviceContext1* context);

	public:

		// デストラクタ
		~DrawString();

		// 出力ウィンドウにログを出力
		inline void DebugLog(const wchar_t* wstr)
		{
#ifndef _DEBUG
			UNREFERENCED_PARAMETER(wstr);
#endif // RELEASE
#ifdef _DEBUG
			OutputDebugString(wstr);
			OutputDebugString(L"\n");
#endif // _DEBUG
		}

		// 文字列描画関数(高木式)
		template <class... Args>
		inline void DrawFormatString(const DirectX::CommonStates& states,
			const DirectX::SimpleMath::Vector2& pos, const DirectX::XMVECTORF32& font_color,
			const wchar_t* format, const Args&... args) noexcept(false)
		{
			// 文字列のサイズを計算
			int texLength = std::swprintf(nullptr, 0, format, args...);
			size_t bufferSize = static_cast<size_t>(texLength) + 1;

			// 文字列バッファを作成
			std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(bufferSize);
			std::swprintf(buffer.get(), bufferSize, format, args...);

			// 文字列の描画
			m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
			m_spriteFont->DrawString(m_spriteBatch.get(), buffer.get(), pos, font_color);
			m_spriteBatch->End();
		}

	private:

		// スプライトバッチ
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		// スプライトフォント
		std::unique_ptr<DirectX::SpriteFont>  m_spriteFont;

	};
}
#endif // DRAWSTRING