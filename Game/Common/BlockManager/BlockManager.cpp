/*
 *	@File	BlockManager.cpp
 *	@Brief	ブロック管理クラス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "Libraries/UserUtility.h"
#include <random>
#include "BlockManager.h"

// 検索用メモ //
// --オブジェクト追記箇所-- //

// コンストラクタ
BlockManager::BlockManager(const wchar_t* stagePath)
	:
	m_stagePath(stagePath),		// ステージパスを格納
	is_playing(false)			// プレイフラグ
{
	// Json読み込みシステム作成
	m_jsonHelper = std::make_unique<JsonHelper>();
	// ダイアログアクセサ作成
	m_dialog = std::make_unique<DiaLog>();

	// ブロックをクリア
	ClearBlocks();
}

// デストラクタ
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_dialog.reset();
	m_stagePath.clear();
	ClearBlocks();
}

// 初期化
void BlockManager::Initialize()
{
	// 一度データを削除
	ClearBlocks();

	// エディタモードの時、判定用エアーで埋める
	if (is_playing == false)
	{
		FillAir();
	}

	// データを読み込む
	m_jsonHelper->Load(m_stagePath.c_str());

	// データを取得
	Json data = m_jsonHelper->GetData();

	for (int i = 0; i < data.size(); i++)
	{
		// 名前を格納
		auto& name = data[i]["Path"];

		// 座標の変換
		float fx = static_cast<float>(data[i]["Position"]["X"]);
		float fy = static_cast<float>(data[i]["Position"]["Y"]);
		float fz = static_cast<float>(data[i]["Position"]["Z"]);
		SimpleMath::Vector3 pos = SimpleMath::Vector3(fx, fy, fz);

		if (name == "Flozen")	m_flozens.push_back(std::make_unique<Flozen>(pos));		// 氷床
		if (name == "Cloud")	m_clouds.push_back(std::make_unique<Cloud>(pos));		// 雲
		if (name == "Coin")	    m_coins.push_back(std::make_unique<Coin>(pos));			// コイン
		if (name == "Player")	m_chara.push_back(std::make_unique<EditChara>(pos));	// キャラ
		if (name == "Goal")	    m_goals.push_back(std::make_unique<Goal>(pos));			// ゴール
		if (name == "Spike")	m_spikes.push_back(std::make_unique<Spike>(pos));		// 棘

		// --オブジェクト追記箇所-- // 

		// エディタ時のみ実行
		if (not is_playing)
		{
			// 同じ場所にエアーがあったらその場所のエアーを消す
			if (not UserUtility::IsNull(m_air[i].get()) &&
				m_air[i]->GetPosition() == pos)
			{
				m_air[i].reset();
			}
		}
	}
}

// 更新処理
void BlockManager::Update()
{
	std::vector<BaseObject*> objects;
	if (is_playing == false)
	{
		for (auto& obj : m_chara)   objects.push_back(obj.get());	// キャラ
		for (auto& obj : m_air)	    objects.push_back(obj.get());	// エアー
	}
	for(auto& obj : m_flozens)	    objects.push_back(obj.get());	// 氷床
	for(auto& obj : m_clouds)		objects.push_back(obj.get());	// 雲
	for(auto& obj : m_coins)		objects.push_back(obj.get());	// コイン
	for(auto& obj : m_goals)		objects.push_back(obj.get());	// ゴール
	for(auto& obj : m_spikes)		objects.push_back(obj.get());	// 棘

	// --オブジェクト追記箇所-- // 

	// オブジェクトの更新
	for (auto& obj : objects)
	{
		if (UserUtility::IsNull(obj)) { continue; }
		obj->Update();
	}

	// 置き換え捜査
	ReplaceBlock();
}

// 描画処理
void BlockManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	std::vector<BaseObject*> objects = {};
	if (is_playing == false)
		for (auto& obj : m_chara)   objects.push_back(obj.get());	// キャラ
	for (auto& obj : m_flozens)	    objects.push_back(obj.get());	// 氷床
	for (auto& obj : m_clouds)		objects.push_back(obj.get());	// 雲
	for (auto& obj : m_coins)		objects.push_back(obj.get());	// コイン
	for (auto& obj : m_goals)		objects.push_back(obj.get());	// ゴール
	for (auto& obj : m_spikes)		objects.push_back(obj.get());	// 棘

	// --オブジェクト追記箇所-- // 

	// オブジェクトの描画
	for (auto& obj : objects)
	{
		if (UserUtility::IsNull(obj)) { continue; }
		obj->Draw(context, states, view, proj, wireframe, option);
	}
}

// オフセットを加算(セレクトシーンで主に呼び出す)
void BlockManager::SetOffset(const SimpleMath::Vector3& offset)
{
	std::vector<BaseObject*> objects = {};
	for (auto& obj : m_flozens)	    objects.push_back(obj.get());	// 氷床
	for (auto& obj : m_clouds)		objects.push_back(obj.get());	// 雲
	for (auto& obj : m_coins)		objects.push_back(obj.get());	// コイン
	for (auto& obj : m_goals)		objects.push_back(obj.get());	// ゴール
	for (auto& obj : m_spikes)		objects.push_back(obj.get());	// 棘

	// --オブジェクト追記箇所-- // 

	// オフセットの設定
	for (auto& obj : objects)
	{
		if (UserUtility::IsNull(obj)) { continue; }
		obj->SetPosition(obj->GetInitialPosition() + offset);
	}
}

// ブロックの種類から書き出し用文字列を返す
std::string BlockManager::GetBlockID(const ID& id)
{
	switch (id)
	{
	case ID::Obj_Flozen:	return "Flozen";// 氷床
	case ID::Obj_Cloud:		return "Cloud";	// 雲
	case ID::Obj_Coin:	    return "Coin";	// コイン
	case ID::Obj_Player:	return "Player";// キャラ
	case ID::Obj_Goal:		return "Goal";	// ゴール
	case ID::Obj_Spike:		return "Spike";	// 棘
	default:		        return "";
	}

	// --オブジェクト追記箇所-- // 
}

// ブロック置き換え処理
void BlockManager::ReplaceBlock()
{
	ReplaceObjects(ID::Obj_Flozen, m_flozens);	// 氷床
	ReplaceObjects(ID::Obj_Cloud,  m_clouds);	// 雲
	ReplaceObjects(ID::Obj_Coin,   m_coins);	// コイン
	ReplaceObjects(ID::Obj_Air,    m_air);		// エアー
	ReplaceObjects(ID::Obj_Player, m_chara);	// キャラ
	ReplaceObjects(ID::Obj_Goal,   m_goals);	// ゴール
	ReplaceObjects(ID::Obj_Spike,  m_spikes);	// 棘

	// --オブジェクト追記箇所-- // 
}

// ブロック作成
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	if (id == ID::Obj_Flozen)   m_flozens.push_back(std::make_unique<Flozen>(pos));	 // 氷床
	if (id == ID::Obj_Cloud)	m_clouds.push_back(std::make_unique<Cloud>(pos));	 // 雲
	if (id == ID::Obj_Coin)		m_coins.push_back(std::make_unique<Coin>(pos));		 // コイン
	if (id == ID::Obj_Air)		m_air.push_back(std::make_unique<Air>(pos));		 // エアー
	if (id == ID::Obj_Player)	m_chara.push_back(std::make_unique<EditChara>(pos)); // キャラ
	if (id == ID::Obj_Goal)		m_goals.push_back(std::make_unique<Goal>(pos));		 // ゴール
	if (id == ID::Obj_Spike)	m_spikes.push_back(std::make_unique<Spike>(pos));	 // 棘

	// --オブジェクト追記箇所-- // 
}

// ブロック配列をリセットする
void BlockManager::ClearBlocks()
{
	ClearObjects(&m_flozens);		// 氷床
	ClearObjects(&m_clouds);		// 雲
	ClearObjects(&m_coins);			// コイン
	ClearObjects(&m_air);			// エアー
	ClearObjects(&m_chara);			// キャラ
	ClearObjects(&m_goals);			// ゴール
	ClearObjects(&m_spikes);		// 棘

	// --オブジェクト追記箇所-- // 
}

// ステージを書き出す
void BlockManager::OutputStage()
{
	// パスを設定
	auto path = m_dialog->GetExpFilePath();
	if (UserUtility::IsNull(path))	return;
	else m_stagePath = path;

	// パスを設定
	m_jsonHelper->SetPath(m_stagePath.c_str());

	// オブジェクト追加
	std::vector<BaseObject*> object = {};
	AddWriteObjects(&object, m_flozens);	// 氷床
	AddWriteObjects(&object, m_clouds);		// 雲
	AddWriteObjects(&object, m_coins);		// コイン
	AddWriteObjects(&object, m_chara);		// キャラ
	AddWriteObjects(&object, m_goals);		// ゴール
	AddWriteObjects(&object, m_spikes);		// 棘

	// --オブジェクト追記箇所-- // 

	// データ書き出し
	OutputUniqueData(object);
}

// ユニークなデータを書き出す
void BlockManager::OutputUniqueData(std::vector<BaseObject*>& data)
{
	// 重複しているデータを単一データにする
	std::unordered_map<std::string, Json> unique = {};
	for (auto& obj : data)
	{
		if (UserUtility::IsNull(obj)) { continue; }

		std::string id = GetBlockID(obj->GetID());
		SimpleMath::Vector3 position = obj->GetInitialPosition();

		// ブロックの種類と初期位置から一意なキーを生成
		// ID_X_Y_Zという単一キーを作成する(例：Flozen_1_2_1,Cloud_3_3_7)
		std::string uniqueKey = id + "_" + std::to_string(position.x) + "_"
			+ std::to_string(position.y) + "_" + std::to_string(position.z);

		// キーが存在しない場合、エントリにデータを追加
		if (unique.find(uniqueKey) == unique.end())
		{
			unique[uniqueKey]["Path"] = id;
			unique[uniqueKey]["Position"]["X"] = position.x;
			unique[uniqueKey]["Position"]["Y"] = position.y;
			unique[uniqueKey]["Position"]["Z"] = position.z;
		}
	}

	// ユニークエントリをソートして最終出力に登録する
	std::vector<Json> sortedEntries = {};
	for (const auto& entry : unique)
	{
		sortedEntries.push_back(entry.second);
	}

	// 文字列が多い・XZ昇順・Y昇順の優先度でソート
	std::sort(sortedEntries.begin(), sortedEntries.end(), OutputSort());

	// 最終出力処理
	Json output;
	for (const auto& sortedEntry : sortedEntries)
	{
		output.push_back(sortedEntry);
	}

	// インデントをそろえて書き出し
	m_jsonHelper->Write(output.dump(2));
}

// エアーで埋める
void BlockManager::FillAir()
{
	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			for (int z = 0; z < MAP_SIZE_Z; z++)
			{
				float fx = static_cast<float>(x);
				float fy = static_cast<float>(y);
				float fz = static_cast<float>(z);
				SimpleMath::Vector3 pos = SimpleMath::Vector3(fx, fy, fz);
				m_air.push_back(std::make_unique<Air>(pos));
			}
		}
	}
}

// プレイヤーの座標を取得する
SimpleMath::Vector3 BlockManager::GetPlayerPosition() const
{
	SimpleMath::Vector3 pos;

	// プレイヤーが１つしかない場合はその座標を返す
	// プレイヤーが２つ以上ある場合はランダムで返す
	if (m_chara.size() == 1)
	{
		pos = m_chara[0]->GetInitialPosition();
	}
	else
	{
		// 乱数を生成する
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dist(0, static_cast<int>(m_chara.size()) - 1);

		// ランダムに1人のプレイヤーを選び、その座標を返す
		int idx = dist(gen);
		pos = m_chara[idx]->GetInitialPosition();
	}

	return pos;
}

// ゴール判定取得
bool BlockManager::IsArrived() const
{
	if (m_goals.empty()) return false;

	for (auto& goal : m_goals)
	{
		if (goal->IsHitFlag())
		{
			return true;
		}
	}
	return false;
}

// 棘の衝突取得
bool BlockManager::IsHitSpike() const
{
	if (m_spikes.empty()) return false;

	for (auto& spike : m_spikes)
	{
		if (spike->IsHitFlag())
		{
			return true;
		}
	}
	return false;
}

// エクスプローラーからパスを取得する
void BlockManager::ReLoad(const wchar_t* path)
{
	// 開けなかったときのために一時保存する
	std::wstring tmp = m_stagePath;

	// ダイアログが作られていなければ文字列を返さない
	if (UserUtility::IsNull(m_dialog.get())) return;

	// ブロックをすべて破棄する
	ClearBlocks();

	// パスがなかったらダイアログから開く
	if (UserUtility::IsNull(path))
	{
		auto dialogPath = m_dialog->GetExpFilePath();
		if (not UserUtility::IsNull(dialogPath))
		{
			m_stagePath = dialogPath;
		}
	}
	else
	{
		m_stagePath = path;
	}

	// ファイルの内容チェック(中身が空なら最初のパスを再代入)
	if (m_stagePath.empty())
	{
		m_stagePath = tmp;
	}

	// 初期化する
	Initialize();
}
