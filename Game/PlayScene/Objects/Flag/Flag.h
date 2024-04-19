/*
 *	@File	Flag.h
 *	@Brief	旗オブジェクト
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAG
#define FLAG

// 親オブジェクトクラス
#include "Game/Bases/BaseObject.h"

class Flag : public BaseObject
{
public:

	// 到着状況を取得(到着したらTrue)
	bool IsArrive() const { return is_arrive; }

	// コンストラクタ
	Flag(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& dropped);
	// デストラクタ
	~Flag();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;


private:

	// 到着みなし値
	static const float CLOSED_MATCH;
	// 落下速度
	static const float FALL_SPEED;

private:

	// 落下位置
	DirectX::SimpleMath::Vector3 m_droppedPosition;
	// 到着フラグ
	bool is_arrive;

};

#endif // FLAG