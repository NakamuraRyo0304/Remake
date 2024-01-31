/*
 *	@File	Animation2DSprite.h
 *	@Brief	2Dスプライトのアニメーションクラス。
 *	@Date	2023-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ANIMATION2DSPRITE
#define ANIMATION2DSPRITE

//==============================================================================
// エイリアス宣言
//==============================================================================
using PrimitiveVertex = PrimitiveBatch<VertexPositionColorTexture>;

class Animation2DSprite
{
private:

	//==============================================================================
	// シェーダーの定義(頂点・ピクセル・ジオメトリ)
	//==============================================================================
	struct Shaders
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		VS;			// 頂点シェーダー
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		PS;			// ピクセルシェーダー
		Microsoft::WRL::ComPtr<ID3D11GeometryShader>	GS;			// ジオメトリシェーダー
	};

	//==============================================================================
	// コンスタントバッファの定義
	//==============================================================================
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		World;						// ワールド行列
		DirectX::SimpleMath::Matrix		View;						// ビュー行列
		DirectX::SimpleMath::Matrix		Proj;						// プロジェクション行列
		DirectX::SimpleMath::Vector4    Move;						// 変動する値
	};

	//==============================================================================
	// 型のサイズの定義
	//==============================================================================
	const UINT SV3 = sizeof(DirectX::SimpleMath::Vector3);			// Vector3のサイズ
	const UINT SV4 = sizeof(DirectX::SimpleMath::Vector4);			// Vector4のサイズ
	const UINT SV7 = SV3 + SV4;										// SV3とSV4の総和
	const D3D11_INPUT_CLASSIFICATION V_DATA = D3D11_INPUT_PER_VERTEX_DATA;	// 頂点データ

	//==============================================================================
	// インプットレイアウトの作成
	//==============================================================================
	const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	V_DATA, 0 },
		{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, SV3,	V_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, SV7,	V_DATA, 0 },
	};

private:

	// プリミティブバッチ
	std::unique_ptr<PrimitiveVertex> m_batch;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// シェーダー
	std::unique_ptr<Shaders> m_shaders;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// テクスチャの座標（三次元）
	DirectX::SimpleMath::Vector3 m_position;


public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	Animation2DSprite();
	~Animation2DSprite();

	/// <summary>
	/// リソースの作成
	/// </summary>
	/// <param name="path">テクスチャパス</param>
	/// <returns>なし</returns>
	void CreateResources(const wchar_t* path);

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <returns>なし</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// ビルボード化関数
	/// </summary>
	/// <param name="eye">カメラ位置</param>
	/// <param name="target">注視点</param>
	/// <param name="up">上方向</param>
	/// <returns>なし</returns>
	void CreateBillboard(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 target, DirectX::SimpleMath::Vector3 up);

	// 座標を設定
	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_position = pos; }

private:

	/// <summary>
	/// コンスタントバッファ作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateConstBuffer();

	/// <summary>
	/// シェーダーの作成
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>頂点シェーダーのデータ</returns>
	std::vector<uint8_t> CreateShaders();

	/// <summary>
	/// インプットレイアウトの作成
	/// </summary>
	/// <param name="vs">頂点シェーダー</param>
	/// <returns>なし</returns>
	void CreateInputLayout(std::vector<uint8_t> vs);
};

#endif // ANIMATION2DSPRITE