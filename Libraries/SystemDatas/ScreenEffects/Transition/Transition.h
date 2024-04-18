/*
 *	@File	Transition.h
 *	@Brief	場面切り替えのトランジション。
 *	@Date	2023-10-28
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TRANSITION
#define TRANSITION

class Transition
{
public:

	// コンスタントバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		World;
		DirectX::SimpleMath::Matrix		View;
		DirectX::SimpleMath::Matrix		Proj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};

	// インプットレイアウトの設定
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

public:

	// 色を取得
	DirectX::XMVECTORF32 GetColor() const { return m_color; }
	// 色を設定(デフォルトで黒)
	void SetColor(const DirectX::XMVECTORF32& color = DirectX::Colors::Black) { m_color = color; }

	// コンストラクタ
	Transition();
	// デストラクタ
	~Transition();
	// リソースの作成
	void Create(const wchar_t* path);
	// 描画
	void Draw(const float& timer);

private:

	// 画像読み込み
	void LoadTexture(const wchar_t* path);
	// シェーダーの作成
	void CreateShader();
	// コンスタントバッファ作成
	void CreateConstBuffer();

private:

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// 頂点
	DirectX::VertexPositionColorTexture m_vertice;
	// テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// フェード色
	DirectX::XMVECTORF32 m_color;

	// バーテックスシェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_verShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geoShader;
	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBuffer;

};

#endif // TRANSITION