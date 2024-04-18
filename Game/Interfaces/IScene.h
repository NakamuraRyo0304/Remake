/*
 *	@File	IScene.h
 *	@Brief	シーンのインターフェース
 *	@Date	2024-04-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ISCENE
#define	ISCENE

class IScene
{
public:

	// コンストラクタ
	IScene() = default;
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

	// シーン内の変数の初期化関数
	virtual void SetSceneValues() = 0;
	// デバッグ描画
	virtual void DebugDraw(DirectX::CommonStates& states) = 0;

};

#endif // ISCENE