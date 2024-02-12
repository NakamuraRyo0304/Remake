/*
 *	@File	Stage4Camera.h
 *	@Brief	ステージ４のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE4CAMERA
#define STAGE4CAMERA

class Stage4Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	Stage4Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage4Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // STAGE4CAMERA