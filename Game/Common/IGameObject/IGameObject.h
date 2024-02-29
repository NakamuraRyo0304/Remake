/*
 *	@File	IGameObject.h
 *	@Brief	ゲームオブジェクト。
 *	@Date	2023-11-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef IGAMEOBJECT
#define IGAMEOBJECT

//==============================================================================
// オブジェクトのステータス
//==============================================================================
#include "IGameObjectStates.h"

class IGameObject
{
private:
	// ---モデルデータ---
	std::unique_ptr<DirectX::Model> m_model;

	// ---モデルパス---
	const wchar_t* m_filePath;
	// ---ディレクトリパス---
	const wchar_t* m_directoryPath;

	// ---ワールド行列---
	DirectX::SimpleMath::Matrix m_world;		// このオブジェクトのマトリクス
	DirectX::SimpleMath::Matrix m_parentMatrix;	// 親のオブジェクトのマトリクス

private:

	// ---座標---
	DirectX::SimpleMath::Vector3 m_position;		// 現在の座標
	DirectX::SimpleMath::Vector3 m_initialPosition;	// 初期の座標
	// ---スケール---
	DirectX::SimpleMath::Vector3 m_scale;			// 現在のスケール
	DirectX::SimpleMath::Vector3 m_initialScale;	// 初期のスケール
	// ---回転---
	DirectX::SimpleMath::Vector3 m_rotate;

	// ---オブジェクトID---
	ID m_id;

	// ---オブジェクトの重さ---
	double m_weight;

	// ---アクティブフラグ---
	bool is_active;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mpath">モデルパス</param>
	/// <param name="dpath">ディレクトリパス</param>
	/// <param name="pos">初期位置</param>
	/// <returns>なし</returns>
	IGameObject(const wchar_t* mpath, const wchar_t* dpath,
		DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3::Zero);
	~IGameObject() = default;
	bool operator==(const IGameObject& other) const
	{
		bool _id = m_id == other.m_id;
		bool _iniPos = m_initialPosition == other.m_initialPosition;
		bool _weight = m_weight == other.m_weight;
		return _id && _iniPos && _weight;
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	virtual void Update() = 0;
	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	virtual void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states,
		DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) = 0;

public:

	// 座標を取得
	DirectX::SimpleMath::Vector3 GetPosition()        const { return m_position; }
	// 初期座標を取得
	DirectX::SimpleMath::Vector3 GetInitialPosition() const { return m_initialPosition; }
	// スケールを取得
	DirectX::SimpleMath::Vector3 GetScale()           const { return m_scale; }
	// 初期スケールを取得
	DirectX::SimpleMath::Vector3 GetInitialScale()    const { return m_initialScale; }
	// 回転を取得
	DirectX::SimpleMath::Vector3 GetRotate()          const { return m_rotate; }
	// ワールドマトリクスを取得
	DirectX::SimpleMath::Matrix GetWorldMatrix()      const { return m_world; }
	// 親のマトリクスを取得
	DirectX::SimpleMath::Matrix GetParentMatrix()     const { return m_parentMatrix; }
	// IDを取得
	ID GetID()                                        const { return m_id; }
	// 重さを取得
	double GetWeight()                                const { return m_weight; }
	// アクティブ状況を取得
	bool IsActive()									  const { return is_active; }
	// モデルを参照する
	std::unique_ptr<DirectX::Model>& GetModel()				{ return m_model; }

public:

	// 座標を設定
	void SetPosition(const DirectX::SimpleMath::Vector3& pos)        { m_position = pos; }
	// 初期座標を設定
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }
	// スケールを設定
	void SetScale(const DirectX::SimpleMath::Vector3& scale)         { m_scale = scale; }
	// 初期スケールを設定
	void SetInitialScale(const DirectX::SimpleMath::Vector3& scale)  { m_initialScale = scale; }
	// 回転を設定
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate)       { m_rotate = rotate; }
	// 親のマトリクスを設定
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix)  { m_parentMatrix = matrix; }
	// IDを設定
	void SetID(const ID& id)                                         { m_id = id; }
	// 重さを設定
	void SetWeight(const double& weight)                             { m_weight = weight; }
	// アクティブ状況を設定
	void SetActive(const bool& flag)								 { is_active = flag; }

public:
	// ワールドマトリクスを作成
	void CreateWorldMatrix();
	// モデルを作成する
	void CreateModel();
	// モデルをリリースする
	void ReleaseModel();
	// モデルを変更する
	void ChangeModel(const wchar_t* path);
};

#endif // IGAMEOBJECT