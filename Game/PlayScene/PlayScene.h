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
class FlagManager;
class ImageShot;
class Sky_Play;
class StageCollision;
class Timer;
class Player;
class UI_Play;
class WorldMouse;
class Water;
class PlayScene final : public IScene
{
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

private:

	// 最大追跡数
	static const int MAX_FOLLOW;

	// 旗の開始位置
	static const float FLAG_START;

	// フラグサイズ（カーソル位置）
	static const float FLAG_CURSOR_RATE;

private:

	// シャドウマップのサイズ
	static const int SHADOWMAP_SIZE;

	// ライトの位置/回転/範囲の角度/環境光の色
	static const DirectX::SimpleMath::Vector3 LIGHT_POSITION;
	static const DirectX::SimpleMath::Quaternion LIGHT_ROTATION;
	static const float LIGHT_THETA;
	static const float AMBIENT_COLOR;

	// ライトのニアクリップ・ファークリップ
	const float LIGHT_NEAR = 0.1f;
	const float LIGHT_FAR = 250.0f;

private:

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

	// シャドウ/ライトバッファ
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_shadowConstant, m_lightConstant;


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

public:

	// ゲームタイマーを取得する
	const float& GetGameTimer() { return m_gameTimer; }

	// 集めたコイン数を取得する
	const int& GetCollectedCoin() { return m_collectedCoin; }

private:

	// ステージ番号に応じてパスを返す
	const wchar_t* GetStagePath();

};

#endif // PlayScene