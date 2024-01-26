/*
 *	@File	Stage1Camera.h
 *	@Brief	ステージ１のセレクトカメラ。
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

//==============================================================================
// 親カメラクラス
//==============================================================================
#include "Game/Common/IGameCamera/IGameCamera.h"

#ifndef STAGE1CAMERA
#define STAGE1CAMERA

class Stage1Camera : public IGameCamera
{
private:

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="screenSize">スクリーンサイズ</param>
	/// <returns>なし</returns>
	Stage1Camera(const DirectX::SimpleMath::Vector2& screenSize);
	~Stage1Camera();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
};

#endif // STAGE1CAMERA