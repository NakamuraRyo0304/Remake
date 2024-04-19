/*
 *	@File	Stage4Camera.h
 *	@Brief	ステージ４のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

// 親カメラクラス
#include "Game/Bases/BaseCamera.h"

#ifndef STAGE4CAMERA
#define STAGE4CAMERA

class Stage4Camera : public BaseCamera
{
public:

	// コンストラクタ
	Stage4Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~Stage4Camera();
	// 更新処理
	void Update() override;
};

#endif // STAGE4CAMERA