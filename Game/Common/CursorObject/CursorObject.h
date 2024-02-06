/*
 *  @File   CursorObject.h
 *  @Brief  3Dカーソルの位置にオブジェクトを描画。
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CURSOROBJECT
#define CURSOROBJECT

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class CursorObject : public IGameObject
{
private:

	// カーソル座標
	DirectX::SimpleMath::Vector3 m_cursorPosition;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="path">モデルパス</param>
	/// <param name="scale">スケール</param>
	/// <returns>なし</returns>
	CursorObject(const wchar_t* path = L"Resources/Models/CursorObj.cmo",
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One * 0.25f);
	~CursorObject();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

public:

	// カーソル座標を取得
	const DirectX::SimpleMath::Vector3& GetCursorPosition() { return m_cursorPosition; }
	// カーソル座標を設定
	void SetCursorPosition(const DirectX::SimpleMath::Vector3& pos) { m_cursorPosition = pos; }

};

#endif // CURSOROBJECT