/*
 *	@File	Stage0Camera.h
 *	@Brief	ステージ０（エディタ）のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE0CAMERA
#define STAGE0CAMERA

class Stage0Camera : public IGameCamera
{
public:

	// コンストラクタ
	Stage0Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~Stage0Camera();
	// 更新処理
	void Update() override;
};

#endif // STAGE0CAMERA