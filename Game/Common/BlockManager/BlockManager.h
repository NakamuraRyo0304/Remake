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

//==============================================================================
// Json変換クラス
//==============================================================================
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "Libraries/SystemDatas/DiaLog/DiaLog.h"

//==============================================================================
// ブロックのインクルード
//==============================================================================
#include "../Blocks/Sand/Sand.h"			// 砂ブロック
#include "../Blocks/Cloud/Cloud.h"			// 雲ブロック
#include "../Blocks/Coin/Coin.h"			// コインブロック
#include "../../Editor/Objects/Air/Air.h"	// ステージエディタ用判定ブロック

class BlockManager
{
private:

	/// <summary>
	/// ファンクタ
	/// ソートの優先順位
	/// </summary>
	/// <returns>条件に応じたソートプロパティ</returns>
	struct SortPriority
	{
		bool operator()(const Json& a, const Json& b) const
		{
			// 優先度①　IDの文字数が短い順にソート
			if (a["Path"].get<std::string>().length() != b["Path"].get<std::string>().length())
			{
				return a["Path"].get<std::string>().length() < b["Path"].get<std::string>().length();
			}

			// 優先度②　IDが同じ場合、XZ座標の昇順にソート
			if (a["Path"].get<std::string>() == b["Path"].get<std::string>())
			{
				if (a["Position"]["X"] != b["Position"]["X"])
				{
					return a["Position"]["X"] < b["Position"]["X"];
				}
				if (a["Position"]["Z"] != b["Position"]["Z"])
				{
					return a["Position"]["Z"] < b["Position"]["Z"];
				}
			}

			// 優先度③　Y座標の昇順にソート
			return a["Position"]["Y"] < b["Position"]["Y"];
		}
	};

	// ブロックオブジェクト
	std::vector<std::unique_ptr<Sand>> m_sands;
	std::vector<std::unique_ptr<Cloud>> m_clouds;
	std::vector<std::unique_ptr<Coin>> m_coins;
	std::vector<std::unique_ptr<Air>> m_air;

	// Json読み込み
	std::unique_ptr<JsonHelper> m_jsonHelper;

	// ダイアログ操作
	std::unique_ptr<DiaLog> m_dialog;

	// パス保存
	std::wstring m_stagePath;

	// 書き出し中フラグ(処理削減)
	bool is_wrighting;

	// プレイ時のフラグ（Trueでエディタ用描画を切る）
	bool is_playing;

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

	// ステージパスを設定
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }

	// ゲームプレイするときはONにする
	void SetPlay(bool play) { is_playing = play; }

	// ワイヤーフレームの切り替えフラグデフォルトはFalse
	void SetWireFrame(bool frame);

public:

	//==============================================================================
	// エディタ使用時に呼び出す関数
	//==============================================================================

	/// <summary>
	/// ファイルをリロードする
	/// </summary>
	/// <param name="path">特定のパスを指定（エクスプローラーから開く場合はなにも入れない）</param>
	/// <returns>なし</returns>
	void ReLoad(const wchar_t* path = nullptr);

	// ステージを書き出す
	void OutputStage();

private:

	// ブロックのIDから文字列を返す(書き出し用)
	std::string GetBlockID(const ID& id);

	// ブロックの種類を変更する
	void ReplaceBlock();

	// ブロック作成
	void CreateBlock(ID id, DirectX::SimpleMath::Vector3 pos);

	// 配列をリセットする
	void ClearBlocks();

	// 空気で埋める
	void FillAir();

public:

	// 砂ブロックの配列を参照
	std::vector<std::unique_ptr<Sand>>& GetSandBlock() { return m_sands; }
	// 雲ブロックの配列を参照
	std::vector<std::unique_ptr<Cloud>>& GetCloudBlock() { return m_clouds; }
	// コインブロックの配列を参照
	std::vector<std::unique_ptr<Coin>>& GetCoinBlock() { return m_coins; }


	// エアーブロックの配列を参照
	std::vector<std::unique_ptr<Air>>& GetAirBlock() { return m_air; }

};

#endif // BLOCKMANAGER