/*
 *  @File   CursorObject.cpp
 *  @Brief  3Dカーソルの位置にオブジェクトを描画。
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "CursorObject.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CursorObject::CursorObject()
	: IGameObject(L"Resources/Models/CursorObj.cmo", L"Resources/Models")
{
	CreateModel();
	SetID(ID::CursorPos);
	SetWeight(1.0f);

	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(SimpleMath::Vector3::One * 0.25f);
	SetInitialScale(GetScale());
}

//==============================================================================
// デストラクタ
//==============================================================================
CursorObject::~CursorObject()
{
	ReleaseModel();
}

//==============================================================================
// 更新処理
//==============================================================================
void CursorObject::Update()
{
	// 座標を設定する
	SetPosition(m_cursorPosition);

	// マトリクスを作成
	CreateWorldMatrix();
}

//==============================================================================
// 描画処理
//==============================================================================
void CursorObject::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}
