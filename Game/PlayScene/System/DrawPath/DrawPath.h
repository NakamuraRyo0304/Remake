/*
 *  @File   DrawPath.h
 *  @Brief  パス描画クラス。
 *  @Date   2024-04-10
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWPATH
#define DRAWPATH

class DrawPath
{
private:

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitive;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="width">太さ</param>
	/// <returns>なし</returns>
	DrawPath(float width);
	~DrawPath();

	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
};

#endif // DRAWPATH