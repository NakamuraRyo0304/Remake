/*
 *	@File	IScene.h
 *	@Brief	基底クラス
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISCENE
#define	ISCENE

#include "Game/GameMain.h"

#include "Libraries/SystemManager/SystemManager.h"
#include "Libraries/Factories/ModelFactory.h"
#include "Libraries/Factories/GeometricFactory.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/SoundManager/SoundManager.h"

using SHEDERLAM = std::function<void __cdecl()>; // ラムダ式の型

class IScene
{
public:

	// フェード用遷移阻止関数
	void StopNextScene() { m_nextScene = SCENE::NONE; is_changeFlag = false; }
	// 画面サイズを設定
	void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_windowSize = size; }
	// 次のシーンを取得
	SCENE GetNextScene() const { return m_nextScene; }
	// シーンフラグを取得
	bool IsChangeSceneFlag() const { return is_changeFlag; }
	// フェード速度アクセサ
	float GetFadeSpeed() const { return m_fadeSpeed; }
	void SetFadeSpeed(const float& speed) { m_fadeSpeed = speed; }
	// フェード値アクセサ
	float GetFadeValue() const { return m_fadeValue; }
	void SetFadeValue(const float& value) { m_fadeValue = value; }
	// システムマネージャを取得
	const std::shared_ptr<SystemManager>& GetSystemManager() { return m_system; }
	// カメラのデフォルトアングルを取得（45.0f）
	const float& GetDefaultCameraAngle() { return DEFAULT_CAMERA_ANGLE; }
	// 画面のサイズを取得
	const DirectX::SimpleMath::Vector2& GetWindowSize() { return m_windowSize; }
	// フルスクリーンサイズを取得
	const DirectX::SimpleMath::Vector2& GetFullHDSize() { return FULL_HD; }
	// フェードが終わって完全に実行可能ならTrueを返す
	bool IsCanUpdate() { is_fadeEnd = static_cast<int>(GetFadeValue()) == 0; return is_fadeEnd; }
	// 遷移先のシーン設定
	void ChangeScene(const SCENE& nextScene) { m_nextScene = nextScene; is_changeFlag = true; }

	// コンストラクタ
	IScene();
	// デストラクタ
	virtual ~IScene() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;
	// 終了
	virtual void Finalize() = 0;
	// 画面依存の初期化
	virtual void CreateWDResources() = 0;

private:

	const float DEFAULT_CAMERA_ANGLE = 45.0f;							// デフォルトのカメラアングル
	const DirectX::SimpleMath::Vector2 FULL_HD = { 1920.0f,1080.0f };	// フルスクリーンサイズ

private:

	// シーン内の変数の初期化関数
	virtual void SetSceneValues() = 0;
	// デバッグ描画
	virtual void DebugDraw(DirectX::CommonStates& states) = 0;

private:

	std::shared_ptr<SystemManager> m_system;							// システムマネージャ
	DirectX::SimpleMath::Vector2 m_windowSize;							// ウィンドウサイズ
	SCENE m_nextScene;													// 次のシーンを指定する
	float m_fadeSpeed;													// フェード速度
	float m_fadeValue;													// フェード値
	bool is_fadeEnd;													// フェード終了
	bool is_changeFlag;													// シーン切り替え判定フラグ

};

#endif // ISCENE