/*
 *	@File	IGameObject.h
 *	@Brief	ゲームオブジェクト。
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

// オブジェクトのステータス
#include "IGameObjectStates.h"

class IGameObject
{
public:

	// 座標を取得
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// 初期座標を取得
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	// 初期座標を設定
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }

	// スケールを取得
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	// スケールを設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	// 初期スケールを取得
	DirectX::SimpleMath::Vector3 GetInitialScale() const { return m_initialScale; }
	// 初期スケールを設定
	void SetInitialScale(const DirectX::SimpleMath::Vector3& scale) { m_initialScale = scale; }

	// 回転を取得
	DirectX::SimpleMath::Vector3 GetRotate() const { return m_rotate; }
	// 回転を設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }

	// ワールドマトリクスを取得
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_world; }
	// 親のマトリクスを設定
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix) { m_parentMatrix = matrix; }
	// 親のマトリクスを取得
	DirectX::SimpleMath::Matrix GetParentMatrix() const { return m_parentMatrix; }

	// IDを取得
	ID GetID() const { return m_id; }
	// IDを設定
	void SetID(const ID& id) { m_id = id; }

	// アクティブ状況を取得
	bool IsActive() const { return is_active; }
	// アクティブ状況を設定
	void SetActive(const bool& flag) { is_active = flag; }

	// モデルを参照する
	std::unique_ptr<DirectX::Model>& GetModel() { return m_model; }

	// ワールドマトリクスを作成
	void CreateWorldMatrix();
	// モデルを作成する
	void CreateModel();
	// モデルをリリースする
	void ReleaseModel();
	// モデルを変更する
	void ChangeModel(const wchar_t* path);

	// コンストラクタ
	IGameObject(const wchar_t* mpath, const wchar_t* dpath,
		DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	// オペレーター
	bool operator==(const IGameObject& data) const
	{
		bool id = m_id == data.m_id;
		bool iniPos = m_initialPosition == data.m_initialPosition;
		return id && iniPos;
	}
	// デストラクタ
	virtual ~IGameObject() = default;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

private:

	// モデルデータ
	std::unique_ptr<DirectX::Model> m_model;
	// モデルパス
	const wchar_t* m_filePath;
	// ディレクトリパス
	const wchar_t* m_directoryPath;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;		// このオブジェクトのマトリクス
	DirectX::SimpleMath::Matrix m_parentMatrix;	// 親のオブジェクトのマトリクス

	// 座標
	DirectX::SimpleMath::Vector3 m_position;		// 現在の座標
	DirectX::SimpleMath::Vector3 m_initialPosition;	// 初期の座標
	// スケール
	DirectX::SimpleMath::Vector3 m_scale;			// 現在のスケール
	DirectX::SimpleMath::Vector3 m_initialScale;	// 初期のスケール
	// 回転
	DirectX::SimpleMath::Vector3 m_rotate;

	// オブジェクトID
	ID m_id;

	// アクティブフラグ
	bool is_active;

};

#endif // IGAMEOBJECT