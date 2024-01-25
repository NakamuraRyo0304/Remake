/*
 *	@File	DisplayEffect.h
 *	@Brief	画面効果。
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DISPLAYEFFECT
#define DISPLAYEFFECT

//==============================================================================
// デプスステンシルのインクルード
//==============================================================================
#include "Libraries/SystemDatas/DepthStencil/DepthStencil.h"

class DisplayEffect
{
public:

	//==============================================================================
	// ディスプレイエフェクトの種類
	//==============================================================================
	enum class DisplayMode
	{
		Default,			// 通常の状態
		BrownTVEffect,		// ブラウン管風画面効果
		MonochromeEffect,	// モノクロ画面効果

		Length,
	};

private:

	//==============================================================================
	// デプスステンシルのモードを定義
	//==============================================================================
	const int USER_DEPTH_MODE = D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL;

	//==============================================================================
	// ステンシルとレンダーターゲットの構造体
	//==============================================================================
	struct ViewPointer
	{
		ID3D11DepthStencilView* pDepthStencil;
		ID3D11RenderTargetView* pRenderTarget;
	};

	//==============================================================================
	// 頂点情報のエイリアス宣言
	//==============================================================================
	using PrimitiveVertex = PrimitiveBatch<VertexPositionColorTexture>;

	//==============================================================================
	// シェーダーパックの定義
	//==============================================================================
	struct ShaderPack
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
		DirectX::SimpleMath::Vector4	Time;						// タイマー
		DirectX::SimpleMath::Matrix		World;						// ワールド行列
		DirectX::SimpleMath::Matrix		View;						// ビュー行列
		DirectX::SimpleMath::Matrix		Proj;						// プロジェクション行列
	};

	//==============================================================================
	// 型のサイズの定義
	//==============================================================================
	const UINT sizeVec3 = sizeof(SimpleMath::Vector3);				// Vector3のサイズ
	const UINT sizeVec4 = sizeof(SimpleMath::Vector4);				// Vector4のサイズ

	//==============================================================================
	// インプットレイアウトの作成
	//==============================================================================
	const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,					D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeVec3,			D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0, sizeVec3 + sizeVec4,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//==============================================================================
	// バーテックスカウント
	//==============================================================================
	static const UINT VERTEX_COUNT;

private:

	// ディスプレイモード
	DisplayMode m_mode;

	// 画面サイズ
	RECT m_size;

	// ワールド座標・拡大率・回転量
	DirectX::SimpleMath::Vector3 m_worldPosition, m_scale, m_rotate;

	// シェーダーパック
	std::unique_ptr<ShaderPack> m_shaders;

	// レンダーターゲットとデプスステンシル
	std::unique_ptr<ViewPointer> m_viewPointer;

	// 入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// プリミティブバッチ
	std::unique_ptr<PrimitiveVertex> m_batch;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// コンスタントバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;

	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResouce;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="rect">画面サイズ</param>
	/// <returns>なし</returns>
	DisplayEffect(RECT rect);
	~DisplayEffect();

	/// <summary>
	/// 画面効果を設定する
	/// </summary>
	/// <param name="mode">画面効果の種類</param>
	/// <returns>なし</returns>
	void Initialize(const DisplayMode& mode);

	/// <summary>
	/// 画面効果開始
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Begin();
	/// <summary>
	/// 画面効果終了
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void End();

	/// <summary>
	/// Start-Endに挟まれたオブジェクトに効果を適用する
	/// </summary>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="flag">Trueでワールド行列に変換</param>
	/// <returns>なし</returns>
	void Apply(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj, const bool& flag = false);

	// 画面効果を設定
	void SetDisplayMode(const DisplayMode& mode);
	DisplayMode const GetDisplayMode() { return m_mode; }
	// 画面サイズを設定
	void SetDisplaySize(const RECT& rect) { m_size = rect; }
	// 座標を設定
	void SetWorldPosition(const DirectX::SimpleMath::Vector3& pos) { m_worldPosition = pos; }
	// スケールを設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale = DirectX::SimpleMath::Vector3::One) { m_scale = scale; }
	// 回転量を設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate = DirectX::SimpleMath::Vector3::Zero)
	{
		m_rotate = DirectX::SimpleMath::Vector3(
			XMConvertToRadians(rotate.x),
			XMConvertToRadians(rotate.y),
			XMConvertToRadians(rotate.z)
		);
	}

private:
	/// <summary>
	/// シェーダーを作成する
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateShaders();

	/// <summary>
	/// シェーダー読み込み
	/// </summary>
	/// <param name="path">ファイルパス</param>
	/// <returns>なし</returns>
	std::vector<uint8_t> ReadShader(const wchar_t* path);
};

#endif // DISPLAYEFFECT