/*
 *  @File   BaseObject.cpp
 *  @Brief  オブジェクトの基底クラス。
 *  @Date   2024-04-19
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/Factories/ModelFactory.h"
#include "BaseObject.h"

// コンストラクタ
BaseObject::BaseObject(const wchar_t* path, const wchar_t* dpath, SimpleMath::Vector3 pos)
	:
	m_world(),					// ワールド行列
	m_parentMatrix(),			// 親ワールド行列
	m_position(pos),			// 座標
	m_initialPosition(pos),		// 初期座標
	m_scale(),					// スケール
	m_initialScale(),			// 初期スケール
	m_rotate(),					// 回転
	m_filePath(path),			// モデルパス
	m_directoryPath(dpath),		// ディレクトリパス
	m_id(ID::Default),			// オブジェクトID
	is_active(true)				// アクティブ状況
{
	CreateWorldMatrix();
}

// デストラクタ
BaseObject::~BaseObject()
{
	ReleaseModel();
}

// ワールド行列を作成
void BaseObject::CreateWorldMatrix()
{
	// スケールを変更
	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(GetScale());
	// 回転を変更
	SimpleMath::Matrix rotate = SimpleMath::Matrix::CreateFromYawPitchRoll(GetRotate());
	// 座標を変更
	SimpleMath::Matrix trans = SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 変更したデータを反映
	m_world = scale * rotate * trans;
}

// モデルを作成
void BaseObject::CreateModel()
{
	m_model = ModelFactory::CreateModel(m_filePath, m_directoryPath);
}

// モデルを解放
void BaseObject::ReleaseModel()
{
	m_model.reset();
}

// モデルを変更
void BaseObject::ChangeModel(const wchar_t* path)
{
	m_filePath = path;
	CreateModel();
}
