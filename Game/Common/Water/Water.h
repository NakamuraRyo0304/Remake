/*
 *  @File   Water.h
 *  @Brief  水面。
 *  @Date   2024-02-08
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef WATER
#define WATER

class Water
{
public:

	// コンストラクタ
	Water();
	// デストラクタ
	~Water();
	// 生成
	void Create(const wchar_t* path);
	// 描画
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	// コンスタントバッファ
	struct ConstantBuffer
	{
		DirectX::SimpleMath::Matrix		World;
		DirectX::SimpleMath::Matrix		View;
		DirectX::SimpleMath::Matrix		Proj;
		float Time;
		float pad[3];
	};
	// 更新が少ないコンスタントバッファ
	struct WaterConstant
	{
		float Scale;
		float pad[3];
	};
	// 画像のスケール
	static const float SCALE;
	// 頂点数
	static const UINT VERTEX_NUM;

private:

	// 画像読み込み
	void LoadTexture(const wchar_t* path);
	// シェーダー作成
	void CreateShader();

private:

	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer, m_waterConstantBuffer;
	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_primitive;
	//コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;
	// テクスチャハンドル
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;

	// シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;		// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;	// ジオメトリシェーダー
	// 行列
	DirectX::SimpleMath::Matrix m_world;				// ワールド行列
	DirectX::SimpleMath::Matrix m_view;					// ビュー行列
	DirectX::SimpleMath::Matrix m_proj;					// プロジェクション行列

};

#endif // WATER