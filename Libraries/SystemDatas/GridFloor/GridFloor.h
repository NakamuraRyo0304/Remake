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
		// エフェクト
		std::unique_ptr<DirectX::BasicEffect> m_basicEffect;

		// プリミティブバッチ
		std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;

		// インプットレイアウト
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

		// 床の一辺のサイズ
		float mSizeX, mSizeY;

		// 分割数
		int m_divsX, m_divsY;

	public:
		GridFloor(const int divsX,const int divsY);
		~GridFloor();

		/// <summary>
		/// 描画処理
		/// </summary>
		/// <param name="states">コモンステート</param>
		/// <param name="view">ビュー行列</param>
		/// <param name="proj">射影行列</param>
		/// <param name="color">グリッドの色</param>
		/// <returns>なし</returns>
		void Draw(DirectX::CommonStates& states,
			const DirectX::SimpleMath::Matrix view,
			const DirectX::SimpleMath::Matrix proj,
			const DirectX::GXMVECTOR color = DirectX::Colors::Gray
		);
	};
}

#endif // GRIDFLOOR