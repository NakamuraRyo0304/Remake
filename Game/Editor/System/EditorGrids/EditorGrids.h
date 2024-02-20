/*
 *  @File   EditorGrids.h
 *  @Brief  エディタ用グリッド。
 *  @Date   2024-02-20
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef EDITORGRIDS
#define EDITORGRIDS

class EditorGrids
{
	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

	// プリミティブバッチ(グリッド用)
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_gridPrimitive;
	// プリミティブバッチ(ライン用)
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_linePrimitive;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// 分割数
	int m_splitX, m_splitZ;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="splitX">X軸の分割数</param>
	/// <param name="splitZ">Z軸の分割数</param>
	/// <returns>なし</returns>
	EditorGrids(const int splitX,const int splitZ);
	~EditorGrids();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="world">ワールド行列</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="color">グリッドの色</param>
	/// <param name="offset">オフセット</param>
	/// <returns>なし</returns>
	void Draw(DirectX::CommonStates& states,
		const DirectX::SimpleMath::Matrix world,
		const DirectX::SimpleMath::Matrix view,
		const DirectX::SimpleMath::Matrix proj,
		const DirectX::GXMVECTOR color = DirectX::Colors::Gray,
		const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3::Zero);

	/// <summary>
	/// 線を描画する
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="world">ワールド行列</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="start">始点</param>
	/// <param name="end">終点</param>
	/// <param name="startColor">始点色</param>
	/// <param name="endColor">終点色</param>
	/// <returns>なし</returns>
	void DrawLine(DirectX::CommonStates& states,
		const DirectX::SimpleMath::Matrix world,
		const DirectX::SimpleMath::Matrix view,
		const DirectX::SimpleMath::Matrix proj,
		const DirectX::SimpleMath::Vector3 start,
		const DirectX::SimpleMath::Vector3 end,
		const DirectX::GXMVECTOR startColor,
		const DirectX::GXMVECTOR endColor);
};

#endif // EDITORGRIDS