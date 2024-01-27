/*
 *	@File	BlockManager.cpp
 *	@Brief	ブロック管理クラス。
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/JsonHelper/JsonHelper.h"
#include "BlockManager.h"

//==============================================================================
// ブロックのインクルード
//==============================================================================
#include "../Blocks/Sand/Sand.h"		// 砂ブロック
#include "../Blocks/Cloud/Cloud.h"		// 雲ブロック
#include "../Blocks/Coin/Coin.h"		// コインブロック


//==============================================================================
// コンストラクタ
//==============================================================================
BlockManager::BlockManager(const wchar_t* stagePath)
	: m_stagePath{ stagePath }		// ステージパスを格納
{
	// Json読み込みシステム作成
	m_jsonHelper = std::make_unique<JsonHelper>();
	m_jsonHelper->Load(m_stagePath.c_str());

	// 初期化処理
	Initialize();
}

//==============================================================================
// デストラクタ
//==============================================================================
BlockManager::~BlockManager()
{
	m_jsonHelper.reset();
	m_stagePath.clear();
	m_parameter.clear();
}

//==============================================================================
// 初期化処理
//==============================================================================
void BlockManager::Initialize()
{
	// データを取得
	Json _data = m_jsonHelper->GetData();
	m_parameter.clear(); m_sands.clear(); m_clouds.clear(); m_coins.clear();

	for (int i = 0; i < _data.size(); i++)
	{
		// 名前を格納
		auto& _name = _data[i]["Path"];

		// 種類
		BlockKinds _kinds = BlockKinds::LENGTHB;

		// 座標の変換
		float _x = static_cast<float>(_data[i]["Position"]["X"]);
		float _y = static_cast<float>(_data[i]["Position"]["Y"]);
		float _z = static_cast<float>(_data[i]["Position"]["Z"]);

		// 砂ブロックを格納
		if (_name == "Sand")
		{
			m_sands.push_back(std::make_unique<Sand>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::SANDB;
		}
		// 雲ブロックを格納
		if (_name == "Cloud")
		{
			m_clouds.push_back(std::make_unique<Cloud>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::CLOUDB;
		}
		// コインブロックを格納
		if (_name == "Coin")
		{
			m_coins.push_back(std::make_unique<Coin>(SimpleMath::Vector3(_x, _y, _z)));
			_kinds = BlockKinds::COINB;
		}

		// ブロック情報を格納する
		m_parameter.push_back(BlockParameter(i, _kinds, SimpleMath::Vector3(_x, _y, _z)));
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
		sand->Update();
	}
	for (auto& cloud : m_clouds)
	{
		cloud->Update();
	}
	for (auto& coin : m_coins)
	{
		coin->Update();
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void BlockManager::Draw(CommonStates& states, SimpleMath::Matrix& view, SimpleMath::Matrix& proj, ShaderLambda option)
{
	// オブジェクトの描画
	for (auto& sand : m_sands)
	{
		sand->Draw(states, view, proj, option);
	}
	for (auto& cloud : m_clouds)
	{
		cloud->Draw(states, view, proj, option);
	}
	for (auto& coin : m_coins)
	{
		coin->Draw(states, view, proj, option);
	}
}

// 衝突通知をおこなう
void BlockManager::NotificateHit(const BlockKinds& kinds, const bool& hit, const int& index)
{
	// ここで条件に一致するオブジェクトを取得して操作
	if (kinds == BlockKinds::SANDB && index >= 0 && index < m_sands.size())
	{
		m_sands[index]->NotificateHit(hit);
	}
	if (kinds == BlockKinds::CLOUDB && index >= 0 && index < m_clouds.size())
	{
		m_clouds[index]->NotificateHit(hit);
	}
	if (kinds == BlockKinds::COINB && index >= 0 && index < m_coins.size())
	{
		m_coins[index]->NotificateHit(hit);
	}
}

//==============================================================================
// ステージを書き出す 仮例
//==============================================================================
void BlockManager::OutputStage()
{
	Json _json;
	for (size_t i = 0; i < m_parameter.size(); i++)
	{
		SimpleMath::Vector3 _pos = m_parameter[i].pos;

		_json[i]["Path"] = GetBlockKinds(m_parameter[i].kinds);
		_json[i]["Position"]["X"] = _pos.x;
		_json[i]["Position"]["Y"] = _pos.y;
		_json[i]["Position"]["Z"] = _pos.z;
	}

	// データを書き出す
	std::string _output = _json.dump(2);
	m_jsonHelper->Write(_output);
}

//==============================================================================
// ブロックの種類から書き出し用文字列を返す
//==============================================================================
std::string BlockManager::GetBlockKinds(const BlockKinds& kinds)
{
	switch (kinds)
	{
	case BlockKinds::SANDB:
		return "Sand";
	case BlockKinds::CLOUDB:
		return "Cloud";
	case BlockKinds::COINB:
		return "Coin";
	default:
		return "nothing";
	}
}
