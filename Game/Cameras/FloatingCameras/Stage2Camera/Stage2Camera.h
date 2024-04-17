/*
 *	@File	Stage2Camera.h
 *	@Brief	ステージ２のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

// 親カメラクラス
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE2CAMERA
#define STAGE2CAMERA

class Stage2Camera : public IGameCamera
{
public:

	// コンストラクタ
	Stage2Camera(const DirectX::SimpleMath::Vector2& screenSize);
	// デストラクタ
	~Stage2Camera();
	// 更新処理
	void Update() override;
};

#endif // STAGE2CAMERA