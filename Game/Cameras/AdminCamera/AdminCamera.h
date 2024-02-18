/*
 *	@File	AdminCamera.h
 *	@Brief	カメラの管理クラス。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ADMINCAMERA
#define ADMINCAMERA

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

//==============================================================================
// 子カメラのインクルード
//==============================================================================
#include "../FixedPointCamera/FixedPointCamera.h"
#include "../FloatingCameras/Stage0Camera/Stage0Camera.h"
#include "../FloatingCameras/Stage1Camera/Stage1Camera.h"
#include "../FloatingCameras/Stage2Camera/Stage2Camera.h"
#include "../FloatingCameras/Stage3Camera/Stage3Camera.h"
#include "../FloatingCameras/Stage4Camera/Stage4Camera.h"
#include "../EditorCamera/EditorCamera.h"
#include "../DeathCamera/DeathCamera.h"

class AdminCamera
{
public:

	// カメラタイプ
	enum Type
	{
		Title_FixedPoint,		// 定点カメラ
		Select0_Floating,		// ステージ０（エディタ）の定点カメラ
		Select1_Floating,		// ステージ１の定点カメラ
		Select2_Floating,		// ステージ２の定点カメラ
		Select3_Floating,		// ステージ３の定点カメラ
		Select4_Floating,		// ステージ４の定点カメラ
		Editor_Moving,			// エディタ時のフリー移動カメラ
		Death_Following,		// 死亡時のカメラ

		Length,					// カメラの数
	};

private:

	// カメラタイプ
	Type m_type;

	// ゲームカメラ
	std::unique_ptr<IGameCamera> m_gameCamera;

	// アクティブフラグ
	bool is_active;

	// ウィンドウサイズ
	DirectX::SimpleMath::Vector2 m_screenSize;

	// 座標/注視点
	DirectX::SimpleMath::Vector3 m_position, m_target;

	// ビュー行列/プロジェクション行列
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// 補間フラグ
	bool is_interpolation;

private:

	// 移動速度
	static const float MOVE_POS_SPEED;

	// 追従速度
	static const float FOLLOW_TARGET_SPEED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	AdminCamera(const DirectX::SimpleMath::Vector2& screenSize);
	~AdminCamera();

	/// <summary>
	/// カメラの更新
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

public:
	//==============================================================================
	// 取得・設定関数
	//==============================================================================

	/// <summary>
	/// アクティブ状態を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>アクティブ状況</returns>
	const bool& IsActive() { return is_active; }
	/// <summary>
	/// アクティブ状態を設定
	/// </summary>
	/// <param name="flag">アクティブ状態</param>
	/// <returns>なし</returns>
	void SetActive(const bool& flag) { is_active = flag; }
	/// <summary>
	/// カメラタイプを取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>カメラタイプ</returns>
	const Type& GetType() { return m_type; }
	/// <summary>
	/// カメラタイプを設定
	/// </summary>
	/// <param name="カメラタイプ"></param>
	/// <returns>なし</returns>
	void SetType(const Type& cameraType);

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>目線の座標</returns>
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="pos">座標</param>
	/// <returns>なし</returns>
	void SetPosition(DirectX::SimpleMath::Vector3 pos);
	/// <summary>
	/// 注視点を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>注視点</returns>
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }
	/// <summary>
	/// 注視点を設定
	/// </summary>
	/// <param name="target">注視点</param>
	/// <returns>なし</returns>
	void SetTarget(DirectX::SimpleMath::Vector3 target);
	/// <summary>
	/// ビュー行列を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>ビュー行列</returns>
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }
	/// <summary>
	/// プロジェクション行列を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>プロジェクション行列</returns>
	DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	/// <summary>
	/// イージングの使用設定
	/// </summary>
	/// <param name="flag">ONで線形補完</param>
	/// <returns>なし</returns>
	void SetInterpolation(bool flag = true) { is_interpolation = flag; }
};

#endif // ADMINCAMERA