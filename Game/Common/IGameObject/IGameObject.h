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

	// ---頂点シェーダー---
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VS;
	// ---ピクセルシェーダー---
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PS;
	// ---ジオメトリシェーダー---
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GS;

	// ---ワールド行列---
	DirectX::SimpleMath::Matrix m_world;		// このオブジェクトのマトリクス
	DirectX::SimpleMath::Matrix m_parentMatrix;	// 親のオブジェクトのマトリクス

private:

	// ---座標---
	DirectX::SimpleMath::Vector3 m_position;		// 現在の座標
	DirectX::SimpleMath::Vector3 m_initialPosition;	// 初期の座標
	// ---スケール---
	DirectX::SimpleMath::Vector3 m_scale;
	// ---回転---
	DirectX::SimpleMath::Vector3 m_rotate;

	// ---オブジェクトID---
	ID m_id;

	// ---オブジェクトの重さ---
	double m_weight;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="mpath">モデルパス</param>
	/// <param name="dpath">ディレクトリパス</param>
	/// <returns>なし</returns>
	IGameObject(const wchar_t* mpath, const wchar_t* dpath);
	~IGameObject();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	virtual void Update() = 0;
	/// <summary>
	/// 描画関数
	/// </summary>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">射影行列</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	virtual void Draw(DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		ShaderLambda option = nullptr) = 0;

public:
	// 座標を取得
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }
	// 座標を設定 param:: pos | 指定座標
	void SetPosition(const DirectX::SimpleMath::Vector3& pos) { m_position = pos; }
	// 初期座標を取得
	const DirectX::SimpleMath::Vector3& GetInitialPosition() { return m_initialPosition; }
	// 初期座標を設定 param:: pos | 指定座標
	void SetInitialPosition(const DirectX::SimpleMath::Vector3& pos) { m_initialPosition = pos; }

	// スケールを取得
	const DirectX::SimpleMath::Vector3& GetScale() { return m_scale; }
	// スケールを設定 param:: scale | 指定スケール
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	// 回転を取得
	const DirectX::SimpleMath::Vector3& GetRotate() { return m_rotate; }
	// 回転を設定 param:: rotate | 指定回転
	void SetRotate(const DirectX::SimpleMath::Vector3& rotate) { m_rotate = rotate; }

	// ワールドマトリクスを作成
	void CreateWorldMatrix();
	// ワールドマトリクスを取得
	const DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_world; }
	// 親のマトリクスを取得
	const DirectX::SimpleMath::Matrix& GetParentMatrix() { return m_parentMatrix; }
	// 親のマトリクスを設定
	void SetParentMatrix(const DirectX::SimpleMath::Matrix& matrix) { m_parentMatrix = matrix; }

	// IDを取得
	const ID& GetID() { return m_id; }
	// IDを設定
	void SetID(const ID& id) { m_id = id; }

	// 重さを取得
	const double& GetWeight() { return m_weight; }
	// 重さを設定
	void SetWeight(const double& weight) { m_weight = weight; }

	// バウンディングボックスを取得
	DirectX::BoundingBox GetBoundingBox() const
	{
		SimpleMath::Vector3 _min = m_position - m_scale * 0.5f;
		SimpleMath::Vector3 _max = m_position + m_scale * 0.5f;
		return DirectX::BoundingBox(_min, _max);
	}

public:
	// モデルを作成する
	void CreateModel();
	// モデルを参照する
	std::unique_ptr<DirectX::Model>& GetModel() { return m_model; }
	// モデルをリリースする
	void ReleaseModel();

public:
	// 頂点シェーダーを作成する
	void CreateVSShader(const wchar_t* vsPath);
	// 頂点シェーダーを取得する
	ID3D11VertexShader* GetVSShader() { return m_VS.Get(); }
	// 頂点シェーダーを設定する
	void SetVSShader(ID3D11VertexShader* vsShader) { m_VS = vsShader; }
	// ピクセルシェーダーを作成する
	void CreatePSShader(const wchar_t* psPath);
	// ピクセルシェーダーを取得する
	ID3D11PixelShader* GetPSShader() { return m_PS.Get(); }
	// ピクセルシェーダーを設定する
	void SetPSShader(ID3D11PixelShader* psShader) { m_PS = psShader; }
	// ジオメトリシェーダーを作成する
	void CreateGSShader(const wchar_t* gsPath);
	// ジオメトリシェーダーを取得する
	ID3D11GeometryShader* GetGSShader() { return m_GS.Get(); }
	// ジオメトリシェーダーを設定する
	void SetGSShader(ID3D11GeometryShader* gsShader) { m_GS = gsShader; }
};

#endif // IGAMEOBJECT