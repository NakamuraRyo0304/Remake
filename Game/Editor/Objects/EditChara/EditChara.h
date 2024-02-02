/*
 *	@File	EditChara.h
 *	@Brief	プレイヤー（エディタ）。
 *	@Date	2024-02-02
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITCHARA
#define EDITCHARA

//==============================================================================
// 親オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class EditChara : public IGameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="position">生成座標</param>
	/// <returns>なし</returns>
	EditChara(DirectX::SimpleMath::Vector3 position);
	~EditChara();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) final;

};
#endif // EDITCHARA