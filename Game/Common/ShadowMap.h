/*
 *  @File   ShadowMap.h
 *  @Brief  シャドウマップ。
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SHADOWMAP
#define SHADOWMAP

class DepthStencil;
class ShadowMap
{
private:

	// シャドウマップのサイズ
	static const int SHADOWMAP_SIZE = 512;

	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;

	// デプスステンシル
	std::unique_ptr<DepthStencil> m_depthStencil;

	// デプス頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vsDep;

	// デプスピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_psDep;

	// ライトの位置
	DirectX::SimpleMath::Vector3 m_lightPosition;

	// ライトの回転
	DirectX::SimpleMath::Quaternion m_lightRotate;

	// シャドウマップのコンスタントバッファ
	struct ShadowBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;	// ライトの位置
		DirectX::XMVECTOR lightDirection;	// ライトの方向
		DirectX::XMVECTOR lightAmbient;		// ライトの環境光
	};

	// シャドウマップバッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant;

	// ライト影響範囲のコンスタントバッファ
	struct LightFovBuffer
	{
		float fCosTheta;		// スポットライトのfov/2
		int pad[3];
	};

	// ライトフォブバッファへのポインタ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_lightConstant;

	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vs;

	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_ps;

	// サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler, m_linearWrap;

	// スポットライトの範囲の角度
	float m_lightTheta;

	// デプスラムダ/シャドウラムダ
	ShaderLambda m_depth, m_shadow;

	// ライトのビューとプロジェクション
	DirectX::SimpleMath::Matrix m_lightView, m_lightProj;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="states">コモンステートポインタ</param>
	/// <returns>なし</returns>
	ShadowMap(DirectX::CommonStates* states);
	~ShadowMap();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

	/// <summary>
	/// 影作成開始
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Begin();

	/// <summary>
	/// 影作成終了
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void End();

	/// <summary>
	/// リリース
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Release();

public:

	// デプスラムダを取得
	ShaderLambda DepthOpt() { return m_depth; }

	// シャドウラムダを取得
	ShaderLambda ShadowOpt() { return m_shadow; }

	// ライトのビュー
	DirectX::SimpleMath::Matrix& GetLightView() { return m_lightView; }

	// ライトのプロジェクション
	DirectX::SimpleMath::Matrix& GetLightProj() { return m_lightProj; }
};

#endif // SHADOWMAP