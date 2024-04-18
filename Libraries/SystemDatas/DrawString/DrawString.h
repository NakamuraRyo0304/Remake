/*
 *	@File	DrawString.h
 *	@Brief	�f�o�b�O�����`��B
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

		// �C���X�^���X�̍쐬���擾
		static Debug::DrawString& GetInstance()
		{
			static DrawString instance(
				DX::DeviceResources::GetInstance()->GetD3DDevice(),
				DX::DeviceResources::GetInstance()->GetD3DDeviceContext()
			);

			return instance;
		}

	private:

		// �R���X�g���N�^
		DrawString(ID3D11Device1* device, ID3D11DeviceContext1* context);

	public:

		// �f�X�g���N�^
		~DrawString();

		// �o�̓E�B���h�E�Ƀ��O���o��
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

		// ������`��֐�(���؎�)
		template <class... Args>
		inline void DrawFormatString(const DirectX::CommonStates& states,
			const DirectX::SimpleMath::Vector2& pos, const DirectX::XMVECTORF32& font_color,
			const wchar_t* format, const Args&... args) noexcept(false)
		{
			// ������̃T�C�Y���v�Z
			int texLength = std::swprintf(nullptr, 0, format, args...);
			size_t bufferSize = static_cast<size_t>(texLength) + 1;

			// ������o�b�t�@���쐬
			std::unique_ptr<wchar_t[]> buffer = std::make_unique<wchar_t[]>(bufferSize);
			std::swprintf(buffer.get(), bufferSize, format, args...);

			// ������̕`��
			m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());
			m_spriteFont->DrawString(m_spriteBatch.get(), buffer.get(), pos, font_color);
			m_spriteBatch->End();
		}

	private:

		// �X�v���C�g�o�b�`
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		// �X�v���C�g�t�H���g
		std::unique_ptr<DirectX::SpriteFont>  m_spriteFont;

	};
}
#endif // DRAWSTRING