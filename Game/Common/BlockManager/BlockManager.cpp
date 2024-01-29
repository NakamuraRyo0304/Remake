/*
 *	@File	BlockManager.cpp
 *	@Brief	ブロック管理クラス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "Libraries/UserUtility.h"
#include "BlockManager.h"

//==============================================================================
// コンストラクタ
//==============================================================================
BlockManager::BlockManager(const wchar_t* stagePath)
	: m_stagePath{ stagePath }		// ステージパスを格納
	, is_playing{ false }			// プレイフラグ
{
	// Json読み込みシステム作成
	m_jsonHelper = std::make_unique<JsonHelper>();

	// ダイアログアクセサ作成
	m_dialog = std::make_unique<DiaLog>();

	// ブロックをクリア
	ClearBlocks();
}

//==============================================================================
// デストラクタ
//==============================================================================
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_dialog.reset();
	m_stagePath.clear();
	ClearBlocks();
}

//==============================================================================
// 初期化処理
//==============================================================================
void BlockManager::Initialize()
{
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

		// 砂ブロックを格納
		if (_name == "Sand")
			m_sands.push_back(std::make_unique<Sand>(_position));
		// コインを格納
		if (_name == "Coin")
			m_coins.push_back(std::make_unique<Coin>(_position));
		// 雲ブロックを格納
		if (_name == "Cloud")
			m_clouds.push_back(std::make_unique<Cloud>(_position));

		// プレイモードはスキップ
		if (is_playing == true) continue;

		// 同じ場所にエアーがあったらその場所のエアーを消す
		if (UserUtility::IsNull(m_air[i].get())) continue;
		if (m_air[i]->GetPosition() == _position)
		{
			m_air[i].reset();
		}
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void BlockManager::Update()
{
	// オブジェクトの更新
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->Update();
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->Update();
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->Update();
	}

	// プレイモードはスキップ
	if (is_playing == true) return;

	for (auto& air : m_air)
	{
		if (UserUtility::IsNull(air.get())) continue;
		air->Update();
	}

	// 置き換え捜査
	ReplaceBlock();
}

//==============================================================================
// 描画処理
//==============================================================================
void BlockManager::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda option)
{
	// オブジェクトの描画
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->Draw(states, view, proj, option);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->Draw(states, view, proj, option);
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->Draw(states, view, proj, option);
	}
}

//==============================================================================
// 衝突通知を送る
//==============================================================================
void BlockManager::NotificateHit(const ID& id, const bool& hit, const int& index)
{
	if (id == ID::Obj_Sand && index >= 0 && index < m_sands.size())
		m_sands[index]->NotificateHit(hit);
	if (id == ID::Obj_Cloud && index >= 0 && index < m_clouds.size())
		m_clouds[index]->NotificateHit(hit);
	if (id == ID::Obj_Coin && index >= 0 && index < m_coins.size())
		m_coins[index]->NotificateHit(hit);


	// プレイ時はスキップ
	if (is_playing) return;

	if (id == ID::Obj_Air && index >= 0 && index < m_air.size())
		m_air[index]->NotificateHit(hit);
}

//==============================================================================
// ワイヤーフレームを設定
//==============================================================================
void BlockManager::SetWireFrame(bool frame)
{
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;
		sand->SetWireFrameFlag(frame);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;
		cloud->SetWireFrameFlag(frame);

	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;
		coin->SetWireFrameFlag(frame);
	}
}

//==============================================================================
// ブロックの種類から書き出し用文字列を返す
//==============================================================================
std::string BlockManager::GetBlockID(const ID& id)
{
	switch (id)
	{
	case ID::Obj_Sand:
		return "Sand";
	case ID::Obj_Coin:
		return "Coin";
	case ID::Obj_Cloud:
		return "Cloud";
	default:
		return "";
	}
}

//==============================================================================
// ブロック置き換え処理
//==============================================================================
void BlockManager::ReplaceBlock()
{
	for (auto& sand : m_sands)
	{
		if (UserUtility::IsNull(sand.get())) continue;

		// 同じならスキップ
		if (sand->GetID() == ID::Obj_Sand) continue;

		// 名前に対応したブロックに変更する
		CreateBlock(sand->GetID(), sand->GetInitialPosition());
		UserUtility::RemoveVec(m_sands, sand);
	}
	for (auto& cloud : m_clouds)
	{
		if (UserUtility::IsNull(cloud.get())) continue;

		// 同じならスキップ
		if (cloud->GetID() == ID::Obj_Cloud) continue;

		// 名前に対応したブロックに変更する
		CreateBlock(cloud->GetID(), cloud->GetInitialPosition());
		UserUtility::RemoveVec(m_clouds, cloud);
	}
	for (auto& coin : m_coins)
	{
		if (UserUtility::IsNull(coin.get())) continue;

		// 同じならスキップ
		if (coin->GetID() == ID::Obj_Coin) continue;

		// 名前に対応したブロックに変更する
		CreateBlock(coin->GetID(), coin->GetInitialPosition());
		UserUtility::RemoveVec(m_coins, coin);
	}
	for (auto& air : m_air)
	{
		if (UserUtility::IsNull(air.get())) continue;

		// 同じならスキップ
		if (air->GetID() == ID::Obj_Air) continue;

		// 名前に対応したブロックに変更する
		CreateBlock(air->GetID(), air->GetInitialPosition());
		UserUtility::RemoveVec(m_air, air);
	}
}

//==============================================================================
// ブロック作成
//==============================================================================
void BlockManager::CreateBlock(ID id, SimpleMath::Vector3 pos)
{
	// IDが一致したモノを追加する

	if (id == ID::Obj_Sand)		// 砂ブロック
		m_sands.push_back(std::make_unique<Sand>(pos));
	if (id == ID::Obj_Cloud)	// 雲ブロック
		m_clouds.push_back(std::make_unique<Cloud>(pos));
	if (id == ID::Obj_Coin)		// コイン
		m_coins.push_back(std::make_unique<Coin>(pos));
	if (id == ID::Obj_Air)		// エアー判定
		m_air.push_back(std::make_unique<Air>(pos));
}

//==============================================================================
// ブロック配列をリセットする
//==============================================================================
void BlockManager::ClearBlocks()
{
	m_sands.clear();
	m_clouds.clear();
	m_coins.clear();
	m_air.clear();
}

//==============================================================================
// エアーで埋める
//==============================================================================
void BlockManager::FillAir()
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			for (int z = 0; z < 10; z++)
			{
				auto _pos = SimpleMath::Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
				m_air.push_back(std::make_unique<Air>(_pos));
			}
		}
	}
}

//==============================================================================
// エクスプローラーからパスを取得する
//==============================================================================
void BlockManager::ReLoad(const wchar_t* path)
{
	// 開けなかったときのために一時保存する
	std::wstring _tmp = m_stagePath;

	// ダイアログが作られていなければ文字列を返さない
	if (UserUtility::IsNull(m_dialog.get())) return;

	// ブロックをすべて破棄する
	ClearBlocks();

	// パスがなかったらダイアログから開く
	if (path == nullptr)
	{
		auto _path = m_dialog->GetExpFilePath();
		if (not UserUtility::IsNull(_path))
		{
			m_stagePath = _path;
		}
	}
	else
	{
		m_stagePath = path;
	}

	// ファイルの内容チェック(中身が空なら最初のパスを再代入)
	if (m_stagePath.empty())
	{
		m_stagePath = _tmp;
	}

	// 初期化する
	Initialize();
}

//==============================================================================
// ステージを書き出す
//==============================================================================
void BlockManager::OutputStage()
{
	// 開けなかったときのために一時保存する
	std::wstring _tmp = m_stagePath;

	// パスを設定
	auto _path = m_dialog->GetExpFilePath();
	if (not UserUtility::IsNull(_path))
	{
		m_stagePath = _path;
	}
	else
	{
		m_stagePath = _tmp;
	}

	// パスを設定
	m_jsonHelper->SetPath(m_stagePath.c_str());

	// オブジェクト配列
	std::vector<IGameObject*> _objects;
	for (auto& sand : m_sands)
	{
		_objects.push_back(sand.get());
	}
	for (auto& cloud : m_clouds)
	{
		_objects.push_back(cloud.get());
	}
	for (auto& coin : m_coins)
	{
		_objects.push_back(coin.get());
	}

	Json _json;
	int _index = 0;

	// _objectに格納されたブロック分出力する
	while (_index < _objects.size())
	{
		_json[_index]["Path"] = GetBlockID(_objects[_index]->GetID());
		SimpleMath::Vector3 _pos = _objects[_index]->GetInitialPosition();

		_json[_index]["Position"]["X"] = _pos.x;
		_json[_index]["Position"]["Y"] = _pos.y;
		_json[_index]["Position"]["Z"] = _pos.z;
		_index++;
	}

	// データを書き出す
	std::string _output = _json.dump(2);
	m_jsonHelper->Write(_output);
}