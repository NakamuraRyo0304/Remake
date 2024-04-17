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
public:

	// コンストラクタ
	EditorGrids(const int splitX, const int splitZ);
	// デストラクタ
	~EditorGrids();
	// 描画
	void Draw(DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix world,
		const DirectX::SimpleMath::Matrix view, const DirectX::SimpleMath::Matrix proj,
		const DirectX::GXMVECTOR color = DirectX::Colors::Gray,
		const DirectX::SimpleMath::Vector3& offset = DirectX::SimpleMath::Vector3::Zero);
	// 線を描画する
	void DrawLine(DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix world,
		const DirectX::SimpleMath::Matrix view, const DirectX::SimpleMath::Matrix proj,
		const DirectX::SimpleMath::Vector3 start, const DirectX::SimpleMath::Vector3 end,
		const DirectX::GXMVECTOR startColor, const DirectX::GXMVECTOR endColor);

private:

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

};

#endif // EDITORGRIDS