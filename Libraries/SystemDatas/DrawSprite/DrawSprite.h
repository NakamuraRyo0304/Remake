/*
 *	@File	DrawSprite.h
 *	@Brief	画像を描画するクラス。
 *	@Date	2023-06-09
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWSPRITE
#define DRAWSPRITE

// デフォルト引数設定用の継承
struct RECT_U : public RECT
{
	RECT_U(LONG left = 0, LONG top = 0, LONG right = 1920, LONG bottom = 1080)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
};

class DrawSprite
{
public:

	// 回転量を設定
	void CreateRotation(const wchar_t* key, const float& rotate);
	// 回転量を取得する
	const float GetRotate(const wchar_t* key) { auto it = m_rotate.find(key); return it->second; }

	// コンストラクタ
	DrawSprite();
	// デストラクタ
	~DrawSprite();

	// スプライトバッチを作成
	void MakeSpriteBatch();
	// スプライトをすべてクリアする
	void Clear();

	// 画像を登録する関数
	void AddTextureData(const wchar_t* key, const wchar_t* path);
	// 描画処理
	void DrawTexture(const wchar_t* key, DirectX::SimpleMath::Vector2 pos,
		DirectX::SimpleMath::Vector4 color, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 origin, RECT_U rect = RECT_U());

private:

	// 画像の格納配列
	std::map<const wchar_t*, const wchar_t*> m_textures;
	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// 画像を描画する変数
	std::map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_SRV;
	// 回転率
	std::map <const wchar_t*, float> m_rotate;

};

#endif // DRAWSPRITE