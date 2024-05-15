/*
 *	@File	BlockManager.h
 *	@Brief	ブロック管理クラス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef BLOCKMANAGER
#define BLOCKMANAGER

#include "Game/Bases/BaseObject.h"						// オブジェクトの基底クラス
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"// JSON関連
#include "Libraries/SystemDatas/DiaLog/DiaLog.h"		// ダイアログ
#include "../Blocks/Flozen/Flozen.h"					// 氷ブロック
#include "../Blocks/Cloud/Cloud.h"						// 雲ブロック
#include "../Blocks/Coin/Coin.h"						// コインブロック
#include "../../Editor/Objects/Air/Air.h"				// ステージエディタ用判定ブロック
#include "../../Editor/Objects/EditChara/EditChara.h"	// ステージエディタ用プレイヤ
#include "../Blocks/Goal/Goal.h"						// ゴールオブジェクト
#include "../Blocks/Spike/Spike.h"						// 棘オブジェクト

class BlockManager
{
public:

	// ファイルをリロードする
	void ReLoad(const wchar_t* path = nullptr);
	// ステージを書き出す
	void OutputStage();
	// ユニークなデータを書き出す
	void OutputUniqueData(std::vector<BaseObject*>& data);

	// 氷床ブロックの配列を参照
	std::vector<std::unique_ptr<Flozen>>&    GetFlozens() { return m_flozens; }
	// 雲ブロックの配列を参照
	std::vector<std::unique_ptr<Cloud>>&     GetClouds() { return m_clouds; }
	// コインブロックの配列を参照
	std::vector<std::unique_ptr<Coin>>&      GetCoins() { return m_coins; }
	// ゴールオブジェクトの配列を参照
	std::vector<std::unique_ptr<Goal>>&      GetGoals() { return m_goals; }
	// 棘オブジェクトの配列を参照
	std::vector<std::unique_ptr<Spike>>&     GetSpikes() { return m_spikes; }
	// エアーブロックの配列を参照
	std::vector<std::unique_ptr<Air>>&       GetAirs() { return m_air; }
	// プレイヤブロックの配列を参照
	std::vector<std::unique_ptr<EditChara>>& GetPlayers() { return m_chara; }
	// ステージパスを取得
	const wchar_t* GetStagePath() { return m_stagePath.c_str(); }
	// ステージパスを設定
	void SetStagePath(const wchar_t* path) { m_stagePath = path; }
	// プレイモードを設定
	void SetPlay(bool play) { is_playing = play; }
	// オフセット
	void SetOffset(const DirectX::SimpleMath::Vector3& offset);
	// プレイヤの座標を取得する
	DirectX::SimpleMath::Vector3 GetPlayerPosition() const;
	// ゴール判定の取得
	bool IsArrived() const;
	// 棘の衝突を取得
	bool IsHitSpike() const;

public:

	// コンストラクタ
	BlockManager(const wchar_t* stagePath);
	// デストラクタ
	~BlockManager();
	// 初期化
	void Initialize();
	// 更新
	void Update();
	/// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

private:

	// ファンクタ
	// アウトプット時のソート条件
	struct OutputSort
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

	// マップのサイズ
	static const int MAP_SIZE_X = 10;
	static const int MAP_SIZE_Y = 5;
	static const int MAP_SIZE_Z = 10;

private:

	// 要素除外用関数
	template<typename T>
	inline void RemoveVec(std::vector<T>& vec, const T& val)
	{
		for (auto it = vec.begin(); it != vec.end(); ++it)
		{
			if (*it == val)
			{
				it = vec.erase(it);
				if (it == vec.end()) break;
			}
		}
	}
	// オブジェクト置き換え関数
	template<typename T>
	void ReplaceObjects(const ID& id, std::vector<T>& objects)
	{
		for (auto& obj : objects)
		{
			if (obj.get() == nullptr) continue;
			if (obj->GetID() == id) continue;
			CreateBlock(obj->GetID(), obj->GetInitialPosition());
			RemoveVec(objects, obj);
		}
	}
	// 書き出し用オブジェクト追加関数
	template <typename T>
	void AddWriteObjects(std::vector<BaseObject*>* objects, std::vector<T>& wish)
	{
		// 空なら処理しない
		if (wish.empty()) return;

		// オブジェクトを追加する
		for (auto& obj : wish)
		{
			objects->push_back(obj.get());
		}
	}
	// クリア関数
	template <typename T>
	bool ClearObjects(std::vector<T>* objects)
	{
		objects->clear();

		return objects->empty();
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

private:

	// ブロックオブジェクト
	std::vector<std::unique_ptr<Flozen>>    m_flozens;	// 氷床
	std::vector<std::unique_ptr<Cloud>>     m_clouds;	// 雲
	std::vector<std::unique_ptr<Coin>>      m_coins;	// コイン
	std::vector<std::unique_ptr<Air>>       m_air;		// 判定用エアー
	std::vector<std::unique_ptr<EditChara>> m_chara;	// キャラ
	std::vector<std::unique_ptr<Goal>>      m_goals;	// ゴール
	std::vector<std::unique_ptr<Spike>>     m_spikes;	// スパイク
	// Json読み込み
	std::unique_ptr<JsonHelper> m_jsonHelper;
	// ダイアログ操作
	std::unique_ptr<DiaLog> m_dialog;
	// パス保存
	std::wstring m_stagePath;
	// プレイ時のフラグ（Trueでエディタ用描画を切る）
	bool is_playing;

};

#endif // BLOCKMANAGER