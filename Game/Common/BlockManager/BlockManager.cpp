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
// --書き換え対象-- //

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
	Json _data = m_jsonHelper->GetData();

	for (int i = 0; i < _data.size(); i++)
	{
		// 名前を格納
		auto& _name = _data[i]["Path"];

		// 座標の変換
		float _x = static_cast<float>(_data[i]["Position"]["X"]);
		float _y = static_cast<float>(_data[i]["Position"]["Y"]);
		float _z = static_cast<float>(_data[i]["Position"]["Z"]);
		SimpleMath::Vector3 _position = SimpleMath::Vector3(_x, _y, _z);

		// --書き換え対象-- //

		// 氷床
		if (_name == "Flozen")	m_flozens.push_back(std::make_unique<Flozen>(_position));
		// 雲
		if (_name == "Cloud")	m_clouds.push_back(std::make_unique<Cloud>(_position));
		// コイン
		if (_name == "Coin")	m_coins.push_back(std::make_unique<Coin>(_position));
		// プレイヤ
		if (_name == "Player")	m_chara.push_back(std::make_unique<EditChara>(_position));
		// ゴール
		if (_name == "Goal")	m_goals.push_back(std::make_unique<Goal>(_position));
		// 棘
		if (_name == "Spike")	m_spikes.push_back(std::make_unique<Spike>(_position));
		// リフト
		if (_name == "Lift")	m_lifts.push_back(std::make_unique<Lift>(_position));

		// エディタ時のみ実行
		if (not is_playing)
		{
			// 同じ場所にエアーがあったらその場所のエアーを消す
			if (not UserUtility::IsNull(m_air[i].get()) &&
				m_air[i]->GetPosition() == _position)
			{
				m_air[i].reset();
			}
		}
	}
}

// 更新処理
void BlockManager::Update()
{
	std::vector<IGameObject*> _objects;

	// --書き換え対象-- //

	if (is_playing == false)
	{
		for (auto& obj : m_chara)   _objects.push_back(obj.get());	// キャラ
		for (auto& obj : m_air)	    _objects.push_back(obj.get());	// エアー
	}
	for(auto& obj : m_flozens)	    _objects.push_back(obj.get());	// 氷床
	for(auto& obj : m_clouds)		_objects.push_back(obj.get());	// 雲
	for(auto& obj : m_coins)		_objects.push_back(obj.get());	// コイン
	for(auto& obj : m_goals)		_objects.push_back(obj.get());	// ゴール
	for(auto& obj : m_spikes)		_objects.push_back(obj.get());	// 棘
	for(auto& obj : m_lifts)		_objects.push_back(obj.get());	// リフト

	// オブジェクトの更新
	for (auto& obj : _objects)
	{
		obj->Update();
	}

	// 置き換え捜査
	ReplaceBlock();
}

// 描画処理
void BlockManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	std::vector<BaseObject*> _objects;

	// --書き換え対象-- //

	if (is_playing == false)
		for (auto& obj : m_chara)   _objects.push_back(obj.get());	// キャラ
	for (auto& obj : m_flozens)	    _objects.push_back(obj.get());	// 氷床
	for (auto& obj : m_clouds)		_objects.push_back(obj.get());	// 雲
	for (auto& obj : m_coins)		_objects.push_back(obj.get());	// コイン
	for (auto& obj : m_goals)		_objects.push_back(obj.get());	// ゴール
	for (auto& obj : m_spikes)		_objects.push_back(obj.get());	// 棘
	for (auto& obj : m_lifts)		_objects.push_back(obj.get());	// リフト

	// オブジェクトの描画
	for (auto& obj : _objects)
		obj->Draw(context, states, view, proj, wireframe, option);
}

// オフセットを加算(セレクトシーンで主に呼び出す)
void BlockManager::SetOffset(const SimpleMath::Vector3& offset)
{
	// --書き換え対象-- //

	for (auto& obj : m_flozens)	// 氷床
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_clouds)	// 雲
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_coins)	// コイン
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_goals)	// ゴール
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_spikes)	// 棘
		obj->SetPosition(obj->GetInitialPosition() + offset);
	for (auto& obj : m_lifts)	// リフト
		obj->SetInitialPosition(obj->GetPosition() + offset);
}

// ブロックの種類から書き出し用文字列を返す
std::string BlockManager::GetBlockID(const ID& id)
{
	// --書き換え対象-- //

	switch (id)
	{
	case ID::Obj_Flozen:	    return "Flozen";// 氷床
	case ID::Obj_Cloud:		    return "Cloud";	// 雲
	case ID::Obj_Coin:	        return "Coin";	// コイン
	case ID::Obj_Player:		return "Player";// キャラ
	case ID::Obj_Goal:		    return "Goal";	// ゴール
	case ID::Obj_Spike:		    return "Spike";	// 棘
	case ID::Obj_Lift:		    return "Lift";	// リフト
	default:		            return "";
	}
}

// ブロック置き換え処理
void BlockManager::ReplaceBlock()
{
	// --書き換え対象-- //

	ReplaceObjects(ID::Obj_Flozen, m_flozens);	// 氷床
	ReplaceObjects(ID::Obj_Cloud,  m_clouds);	// 雲
	ReplaceObjects(ID::Obj_Coin,   m_coins);	// コイン
	ReplaceObjects(ID::Obj_Air,    m_air);		// エアー
	ReplaceObjects(ID::Obj_Player, m_chara);	// キャラ
	ReplaceObjects(ID::Obj_Goal,   m_goals);	// ゴール
	ReplaceObjects(ID::Obj_Spike,  m_spikes);	// 棘
	ReplaceObjects(ID::Obj_Lift,   m_lifts);	// リフト
}

// ブロック作成
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	// --書き換え対象-- //

	if (id == ID::Obj_Flozen)   m_flozens.push_back(std::make_unique<Flozen>(pos));	 // 氷床
	if (id == ID::Obj_Cloud)	m_clouds.push_back(std::make_unique<Cloud>(pos));	 // 雲
	if (id == ID::Obj_Coin)		m_coins.push_back(std::make_unique<Coin>(pos));		 // コイン
	if (id == ID::Obj_Air)		m_air.push_back(std::make_unique<Air>(pos));		 // エアー
	if (id == ID::Obj_Player)	m_chara.push_back(std::make_unique<EditChara>(pos)); // キャラ
	if (id == ID::Obj_Goal)		m_goals.push_back(std::make_unique<Goal>(pos));		 // ゴール
	if (id == ID::Obj_Spike)	m_spikes.push_back(std::make_unique<Spike>(pos));	 // 棘
	if (id == ID::Obj_Lift)		m_lifts.push_back(std::make_unique<Lift>(pos));		 // リフト
}

// ブロック配列をリセットする
void BlockManager::ClearBlocks()
{
	// --書き換え対象-- //

	ClearObjects(&m_flozens);		// 氷床
	ClearObjects(&m_clouds);		// 雲
	ClearObjects(&m_coins);			// コイン
	ClearObjects(&m_air);			// エアー
	ClearObjects(&m_chara);			// キャラ
	ClearObjects(&m_goals);			// ゴール
	ClearObjects(&m_spikes);		// 棘
	ClearObjects(&m_lifts);			// リフト
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

	// オブジェクト配列
	std::vector<BaseObject*> object;

	//==============================================================================
	// 追加するのはここから>>> 書き出し用配列にセット
	//==============================================================================

	// --書き換え対象-- //

	AddWriteObjects(&object, m_flozens);	// 氷床
	AddWriteObjects(&object, m_clouds);		// 雲
	AddWriteObjects(&object, m_coins);		// コイン
	AddWriteObjects(&object, m_chara);		// キャラ
	AddWriteObjects(&object, m_goals);		// ゴール
	AddWriteObjects(&object, m_spikes);		// 棘
	AddWriteObjects(&object, m_lifts);		// リフト


	//==============================================================================
	// <<<追加するのはここまで
	//==============================================================================

	// 重複しているデータを単一データにする
	std::unordered_map<std::string, Json> unique;
	for (auto& obj : object)
	{
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
	std::vector<Json> sortedEntries;
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
	std::string str = output.dump(2);
	m_jsonHelper->Write(str);
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
		auto p = m_dialog->GetExpFilePath();
		if (not UserUtility::IsNull(p))
		{
			m_stagePath = p;
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
