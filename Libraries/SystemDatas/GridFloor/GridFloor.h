/*
 *	@File	GridFloor.h
 *	@Brief	デバッグ用グリッド。
 *	@Date	2021-02-09
 *  @Author T.Matsui
 *  @Editor NakamuraRyo
 */

#pragma once
#ifndef GRIDFLOOR
#define GRIDFLOOR

namespace Debug
{
	/// <summary>
	/// デバッグ表示用のグリッド床を表示するクラス
	/// </summary>
	class GridFloor
	{
	public:

		// コンストラクタ
		GridFloor(const int divsX,const int divsY);
		// デストラクタ
		~GridFloor();

		// 描画
		void Draw(DirectX::CommonStates& states, const DirectX::SimpleMath::Matrix view,
			const DirectX::SimpleMath::Matrix proj, const DirectX::GXMVECTOR color = DirectX::Colors::Gray);

	private:

		// エフェクト
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
		// インプットレイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
		// 床の一辺のサイズ
		float m_sizeX, m_sizeY;
		// 分割数
		int m_divsX, m_divsY;

	};
}

#endif // GRIDFLOOR