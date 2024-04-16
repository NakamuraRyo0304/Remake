/*
 *	@File	AdminCamera.h
 *	@Brief	カメラの管理クラス。
 *	@Date	2023-12-12
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ADMINCAMERA
#define ADMINCAMERA

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

// 子カメラのインクルード
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

	// 移動速度
	static const float MOVE_POS_SPEED;
	// 追従速度
	static const float FOLLOW_TARGET_SPEED;

public:

	// アクティブ状態を取得
	bool IsActive() const { return is_active; }
	// アクティブ状態を設定
	void SetActive(const bool& flag) { is_active = flag; }

	// カメラタイプを取得
	Type GetType() const { return m_type; }
	// カメラタイプを設定
	void SetType(const Type& cameraType);

	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// 座標を設定
	void SetPosition(DirectX::SimpleMath::Vector3 pos);

	// 注視点を取得
	const DirectX::SimpleMath::Vector3& GetTarget() { return m_target; }
	// 注視点を設定
	void SetTarget(DirectX::SimpleMath::Vector3 target);

	// ビュー行列を取得
	DirectX::SimpleMath::Matrix& GetView() { return m_view; }

	// プロジェクション行列を取得
	DirectX::SimpleMath::Matrix& GetProjection() { return m_projection; }
	// プロジェクション行列を作成
	void SetProjection(const DirectX::SimpleMath::Matrix& proj);

	// イージングの使用設定
	void SetInterpolation(bool flag = true) { is_interpolation = flag; }

public:

	// コンストラクタ
	AdminCamera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~AdminCamera();
	// 更新
	void Update();

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
};

#endif // ADMINCAMERA