/*
 *	@File	PlayScene.h
 *	@Brief	プレイシーン。
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef PLAYSCENE
#define	PLAYSCENE

// 親シーンクラス
#include "Game/BaseScene/BaseScene.h"

class AdminCamera;
class BlockManager;
class CursorObject;
class DepthStencil;
class FlagManager;
class ImageShot;
class Iceberg;
class Sky_Play;
class StageCollision;
class Timer;
class Player;
class UI_Play;
class WorldMouse;
class Water;
class PlayScene final : public BaseScene
{
public:

	// ゲームタイマーを取得する
	float GetGameTimer() const { return m_gameTimer; }
	// 集めたコイン数を取得する
	int GetCollectedCoin() const { return m_collectedCoin; }
	// ステージ番号を取得する
	int GetStageNumber() const { return m_stageNumber; }

	// コンストラクタ
	PlayScene(const int& number);
	// デストラクタ
	~PlayScene();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;
	// 終了
	void Finalize() override;
	// 画面依存、デバイス依存の初期化
	void CreateWDResources() override;

private:

	// 最大追跡数
	static const int MAX_FOLLOW;
	// 旗の開始位置
	static const float FLAG_START;
	// フラグサイズ（カーソル位置）
	static const float FLAG_CURSOR_RATE;

	// シャドウマップ=============================================

	// シャドウマップのサイズ
	static const int SHADOWMAP_SIZE;
	// ライトの位置
	const DirectX::SimpleMath::Vector3 LIGHT_POSITION = { 4.5f, 10.0f, 10.0f };
	// ライトの回転
	const DirectX::SimpleMath::Quaternion LIGHT_ROTATION = { 0.80f, 0.30f, -0.20f, 0.50f };
	// 範囲の角度
	static const float LIGHT_THETA;
	// 環境光の色
	static const float AMBIENT_COLOR;
	// ライトの最近距離
	const float LIGHT_NEAR = 0.1f;
	// ライトの最遠距離
	const float LIGHT_FAR = 250.0f;

private:

	// シーン内の変数初期化
	void SetSceneValues() override;
	// デバッグ描画
	void DebugDraw(DirectX::CommonStates& states) override;
	// ステージ番号に応じてパスを返す
	const wchar_t* GetStagePath();

private:

	// ステージ番号・集めたコイン数
	int m_stageNumber, m_collectedCoin;
	// ゲームタイマー
	float m_gameTimer;
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
	// フラグマネージャ
	std::unique_ptr<FlagManager> m_flagManager;
	// スクショ
	std::unique_ptr<ImageShot> m_imageShot;
	// 水面
	std::unique_ptr<Water> m_water;
	// UI
	std::unique_ptr<UI_Play> m_ui;
	// タイマー
	std::unique_ptr<Timer> m_timer;
	// スクショ保存先
	std::wstring m_stageTexPath;
	// 氷山
	std::unique_ptr<Iceberg> m_iceberg, m_smallberg, m_bigberg;

	// シャドウマップ=============================================

	// レンダーテクスチャ
	std::unique_ptr<DX::RenderTexture> m_renderTexture;
	// デプスステンシル
	std::unique_ptr<DepthStencil> m_depthStencil;
	// 頂点シェーダー
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vsDep, m_vs;
	// ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_psDep, m_ps;
	// サンプラー
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
	// バッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant, m_lightConstant;
	// シャドウバッファ
	struct ShadowBuffer
	{
		DirectX::XMMATRIX lightViewProj;	// ライトの投影空間へ座標変換する行列
		DirectX::XMVECTOR lightPosition;	// ライトの位置
		DirectX::XMVECTOR lightDirection;	// ライトの方向
		DirectX::XMVECTOR lightAmbient;		// ライトの環境光
	};
	// ライトバッファ
	struct LightFovBuffer
	{
		float fCosTheta;		// スポットライトのfov/2
		int pad[3];
	};

};

#endif // PlayScene