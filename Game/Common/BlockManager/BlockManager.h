/*
 *	@File	BlockManager.h
 *	@Brief	ブロック管理クラス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BLOCKMANAGER
#define BLOCKMANAGER

//==============================================================================
// オブジェクトクラス
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class JsonHelper;
class Sand;
class Cloud;
class Coin;
class BlockManager
{
public:

	// ブロックの種類
	enum BlockKinds : UINT { SANDB, CLOUDB, COINB, LENGTHB };

	// ブロックの参照用パラメーター
	struct BlockParameter
	{
		int index;
		BlockKinds kinds;
		DirectX::SimpleMath::Vector3 pos;
		BlockParameter(int index, BlockKinds kinds, const DirectX::SimpleMath::Vector3& pos)
			: index(index), kinds(kinds), pos(pos) {};
	};

private:

	// ブロックオブジェクト
	std::vector<std::unique_ptr<Sand>> m_sands;
	std::vector<std::unique_ptr<Cloud>> m_clouds;
	std::vector<std::unique_ptr<Coin>> m_coins;

	// ブロックの名前・座標
	std::vector<BlockParameter> m_parameter;

	// Json読み込み
	std::unique_ptr<JsonHelper> m_jsonHelper;

	// パス保存
	std::wstring m_stagePath;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="stagePath">読み込みステージパス</param>
	/// <returns>なし</returns>
	BlockManager(const wchar_t* stagePath);
	~BlockManager();

	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr);

public:

	/// <summary>
	/// 衝突通知を送る
	/// </summary>
	/// <param name="kinds">通知を送る種類</param>
	/// <param name="hit">設定　接触時：True/非接触時：False</param>
	/// <param name="index">衝突したオブジェクト番号(-1で全通知)</param>
	/// <returns>なし</returns>
	void NotificateHit(const BlockKinds& kinds, const bool& hit, const int& index);

	// ステージパスを設定
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }

	// ステージを書き出す
	void OutputStage();

private:

	// ブロックの種類から文字列を返す(書き出し用)
	std::string GetBlockKinds(const BlockKinds& kinds);

};

#endif // BLOCKMANAGER