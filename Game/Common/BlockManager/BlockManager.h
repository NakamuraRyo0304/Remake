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
#include "../Blocks/Flozen/Flozen.h"					// 氷ブロック
#include "../Blocks/Cloud/Cloud.h"						// 雲ブロック
#include "../Blocks/Coin/Coin.h"						// コインブロック
#include "../../Editor/Objects/Air/Air.h"				// ステージエディタ用判定ブロック
#include "../../Editor/Objects/EditChara/EditChara.h"	// ステージエディタ用プレイヤ
#include "../Blocks/Goal/Goal.h"						// ゴールオブジェクト
#include "../Blocks/Spike/Spike.h"						// 棘オブジェクト

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

private:

	// ブロックオブジェクト
	std::vector<std::unique_ptr<Flozen>> m_flozens;
	std::vector<std::unique_ptr<Cloud>> m_clouds;
	std::vector<std::unique_ptr<Coin>> m_coins;
	std::vector<std::unique_ptr<Air>> m_air;
	std::vector<std::unique_ptr<EditChara>> m_chara;
	std::vector<std::unique_ptr<Goal>> m_goals;
	std::vector<std::unique_ptr<Spike>> m_spikes;

	// Json読み込み
	std::unique_ptr<JsonHelper> m_jsonHelper;

	// ダイアログ操作
	std::unique_ptr<DiaLog> m_dialog;

	// パス保存
	std::wstring m_stagePath;

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
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

public:

	// ステージパスを設定
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }

	// ゲームプレイするときはONにする
	void SetPlay(bool play) { is_playing = play; }

	// オフセット
	void SelectOffset(const DirectX::SimpleMath::Vector3& offset);

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

	/// <summary>
	/// 書き出し用オブジェクト追加関数
	/// </summary>
	/// <param name="objects">書き出しに使用する配列</param>
	/// <param name="wish">任意のオブジェクトベクター配列</param>
	/// <returns>なし</returns>
	template <typename T>
	void AddWriteObjects(std::vector<IGameObject*>* objects, std::vector<T>& wish)
	{
		// 空なら処理しない
		if (wish.empty()) return;

		// オブジェクトを追加する
		for (auto& obj : wish)
		{
			objects->push_back(obj.get());
		}
	}

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
	std::vector<std::unique_ptr<Flozen>>& GetFlozenBlock() { return m_flozens; }
	// 雲ブロックの配列を参照
	std::vector<std::unique_ptr<Cloud>>& GetCloudBlock() { return m_clouds; }
	// コインブロックの配列を参照
	std::vector<std::unique_ptr<Coin>>& GetCoinBlock() { return m_coins; }
	// ゴールオブジェクトの配列を参照
	std::vector<std::unique_ptr<Goal>>& GetGoalObject() { return m_goals; }
	// 棘オブジェクトの配列を参照
	std::vector<std::unique_ptr<Spike>>& GetSpikeEnemy() { return m_spikes; }


	// エアーブロックの配列を参照
	std::vector<std::unique_ptr<Air>>& GetAirBlock() { return m_air; }
	// プレイヤブロックの配列を参照
	std::vector<std::unique_ptr<EditChara>>& GetPlayerBlock() { return m_chara; }

public:

	// プレイヤの座標を取得する
	DirectX::SimpleMath::Vector3 GetPlayerPosition();

	// ゴール判定の取得
	bool IsArrived();

	// 棘の衝突を取得
	bool IsHitSpike();

};

#endif // BLOCKMANAGER