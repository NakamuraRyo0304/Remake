/*
 *	@File	Stage0Camera.h
 *	@Brief	ステージ０（エディタ）のセレクトカメラ。
 *	@Date	2023-02-12
 *  @Author NakamuraRyo
 */

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE0CAMERA
#define STAGE0CAMERA

class Stage0Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	Stage0Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage0Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // STAGE0CAMERA