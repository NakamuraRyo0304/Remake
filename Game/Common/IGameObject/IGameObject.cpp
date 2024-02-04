/*
 *	@File	IGameObject.cpp
 *	@Brief	ゲームオブジェクト。
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "IGameObject.h"

//==============================================================================
// コンストラクタ
//==============================================================================
IGameObject::IGameObject(const wchar_t* path, const wchar_t* dpath, SimpleMath::Vector3 pos)
	: m_world{}						// ワールド行列
	, m_parentMatrix{}				// 親ワールド行列
	, m_position{ pos }				// 座標
	, m_initialPosition{ pos }		// 初期座標
	, m_scale{}						// スケール
	, m_initialScale{}				// 初期スケール
	, m_rotate{}					// 回転
	, m_filePath{ path }			// モデルパス
	, m_directoryPath{ dpath }		// ディレクトリパス
	, m_id{ ID::Default }			// オブジェクトID
	, m_weight{}					// オブジェクトの重さ
{
	m_world = SimpleMath::Matrix::Identity;
	m_parentMatrix = SimpleMath::Matrix::Identity;
	m_id = ID::Default;
	m_weight = NON_WEIGHT;
	CreateWorldMatrix();
}

//==============================================================================
// ワールドマトリクスを作成
//==============================================================================
void IGameObject::CreateWorldMatrix()
{
	// スケールを変更
	SimpleMath::Matrix _scale =
		SimpleMath::Matrix::CreateScale(GetScale());
	// 回転を変更
	SimpleMath::Matrix _rotate =
		SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// 座標を変更
	SimpleMath::Matrix _trans =
		SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 変更したデータを反映
	m_world = _scale * _rotate * _trans;
}

//==============================================================================
// モデルを作成する
//==============================================================================
void IGameObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

//==============================================================================
// モデルを破棄する
//==============================================================================
void IGameObject::ReleaseModel()
{
	m_model.reset();
}

//==============================================================================
// モデルを変更する
//==============================================================================
void IGameObject::ChangeModel(const wchar_t* path)
{
	m_filePath = path;
	CreateModel();
}