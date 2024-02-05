/*
 *	@File	PlayScene.h
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYSCENE
#define	PLAYSCENE

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/IScene/IScene.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class DepthStencil;
class Sky_Play;
class StageCollision;
class Player;
class WorldMouse;
class PlayScene final : public IScene
{
private:

	// ステージ番号
	int m_stageNumber;

	// アドミンカメラ
	std::unique_ptr<AdminCamera> m_adminCamera;

	// スカイ球
	std::unique_ptr<Sky_Play> m_sky;

	// プレイヤー
	std::unique_ptr<Player> m_player;

	// ワールドマウス
	std::unique_ptr<WorldMouse> m_worldMouse;

	// ブロックマネージャ
	std::unique_ptr<BlockManager> m_blockManager;

	// ステージの当たり判定
	std::unique_ptr<StageCollision> m_stageCollision;

	// カーソルオブジェクト
	std::unique_ptr<CursorObject> m_cursorObject;

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
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	// スポットライトの範囲の角度
	float m_lightTheta;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="number">ステージ番号</param>
	/// <returns>なし</returns>
	PlayScene(const int& number);
	~PlayScene();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw() override;
	/// <summary>
	/// 終了処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Finalize() override;
	/// <summary>
	/// 画面依存、デバイス依存の初期化
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void CreateWDResources() override;

private:

	/// <summary>
	/// シーン内の変数初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void SetSceneValues() override;
	/// <summary>
	/// デバッグ描画
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <returns>なし</returns>
	void DebugDraw(DirectX::CommonStates& states) override;

private:

	// ステージ番号に応じてパスを返す
	const wchar_t* GetStagePath();

};

#endif // PlayScene