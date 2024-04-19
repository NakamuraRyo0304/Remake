/*
 *	@File	Stage1Camera.h
 *	@Brief	ステージ１のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// 親カメラクラス
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE1CAMERA
#define STAGE1CAMERA

class Stage1Camera : public BaseCamera
{
public:

	// コンストラクタ
	Stage1Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~Stage1Camera();
	// 更新処理
	void Update() override;
};

#endif // STAGE1CAMERA