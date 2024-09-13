/*
 *  @File   CursorObject.cpp
 *  @Brief  3Dカーソルの位置にオブジェクトを描画。
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "CursorObject.h"

// コンストラクタ
CursorObject::CursorObject(const wchar_t* path, SimpleMath::Vector3 scale)
	:
	BaseObject(path, L"Resources/Models")
{
	CreateModel();
	SetID(ID::PE_Cursor_Object);
	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(scale);
	SetInitialScale(GetScale());
}

// デストラクタ
CursorObject::~CursorObject()
{
	ReleaseModel();
}

// 更新
void CursorObject::Update()
{
	// 座標を設定する
	SetPosition(m_cursorPosition);

	// マトリクスを作成
	CreateWorldMatrix();
}

// 描画
void CursorObject::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}
