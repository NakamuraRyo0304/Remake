/*
 *	@File	Air.cpp
 *	@Brief	判定用オブジェクト（エディタ）。
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Air.h"

// コンストラクタ
Air::Air(SimpleMath::Vector3 position)
	:
	IGameObject(L"Resources/Models/Flozen.cmo", L"Resources/Models"),
	is_hit(false)		// 衝突フラグ
{
	CreateModel();
	SetID(ID::Obj_Air);
	SetPosition(SimpleMath::Vector3(position));
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.5f);
}

// デストラクタ
Air::~Air()
{
	ReleaseModel();
}

// 更新
void Air::Update()
{

}

// 描画
void Air::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	UNREFERENCED_PARAMETER(context);
	UNREFERENCED_PARAMETER(states);
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(proj);
	UNREFERENCED_PARAMETER(wireframe);
	UNREFERENCED_PARAMETER(option);
}