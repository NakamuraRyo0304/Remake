/*
 *	@File	Stage2Camera.h
 *	@Brief	ステージ２のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE2CAMERA
#define STAGE2CAMERA

class Stage2Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	Stage2Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage2Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // STAGE2CAMERA