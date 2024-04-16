/*
 *  @File   CursorObject.h
 *  @Brief  3Dカーソルの位置にオブジェクトを描画。
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CURSOROBJECT
#define CURSOROBJECT

// 親オブジェクトクラス
#include "Game/Common/IGameObject/IGameObject.h"

class CursorObject : public IGameObject
{
public:

	// カーソル座標を取得
	DirectX::SimpleMath::Vector3 GetCursorPosition() const { return m_cursorPosition; }
	// カーソル座標を設定
	void SetCursorPosition(const DirectX::SimpleMath::Vector3& pos) { m_cursorPosition = pos; }

	// コンストラクタ
	CursorObject(const wchar_t* path = L"Resources/Models/CursorObj.cmo",
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One * 0.25f);
	// デストラクタ
	~CursorObject();
	// 更新
	void Update() override;
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// カーソル座標
	DirectX::SimpleMath::Vector3 m_cursorPosition;

};

#endif // CURSOROBJECT