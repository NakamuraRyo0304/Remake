/*
 *	@File	Stage3Camera.h
 *	@Brief	ステージ３のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE3CAMERA
#define STAGE3CAMERA

class Stage3Camera : public IGameCamera
{
public:

	// コンストラクタ
	Stage3Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~Stage3Camera();
	// 更新
	void Update() override;
};

#endif // STAGE3CAMERA