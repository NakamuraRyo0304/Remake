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
private:

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
	static const float WATER_SCALE;

	// 頂点数
	static const UINT VERTEX_NUM;

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

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;

	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;

	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_gs;

	// 行列
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

private:

	// インプットレイアウト
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Water();
	~Water();

	/// <summary>
	/// 生成関数
	/// </summary>
	/// <param name="path">画像パス</param>
	/// <returns>なし</returns>
	void Create(const wchar_t* path);

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	/// <summary>
	/// 画像読み込み
	/// </summary>
	/// <param name="path">画像パス</param>
	/// <returns>なし</returns>
	void LoadTexture(const wchar_t* path);

	/// <summary>
	/// シェーダー作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateShader();
};

#endif // WATER