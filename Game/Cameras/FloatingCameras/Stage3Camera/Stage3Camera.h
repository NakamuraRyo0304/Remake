/*
 *	@File	Stage3Camera.h
 *	@Brief	ステージ３のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE3CAMERA
#define STAGE3CAMERA

class Stage3Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	Stage3Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage3Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // STAGE3CAMERA