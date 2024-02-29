/*
 *  @File   FlagManager.h
 *  @Brief  旗管理クラス。
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAGMANAGER
#define FLAGMANAGER

class Flag;
class FlagManager
{
private:

	// 旗の描画位置
	std::vector<std::unique_ptr<Flag>> m_flags;

	// 先頭座標
	DirectX::SimpleMath::Vector3 m_firstPosition;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	FlagManager();
	~FlagManager();

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="context">コンテキスト</param>
	/// <param name="states">コモンステート</param>
	/// <param name="view">ビュー行列</param>
	/// <param name="proj">プロジェクション行列</param>
	/// <param name="wireframe">ワイヤーフレーム</param>
	/// <param name="option">シェーダー等ラムダ式</param>
	/// <returns>なし</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

public:

	/// <summary>
	/// フラグを追加
	/// </summary>
	/// <param name="start">最初の位置</param>
	/// <param name="dropped">落下位置</param>
	/// <param name="max">最大数</param>
	/// <returns>なし</returns>
	void AddFlag(DirectX::SimpleMath::Vector3 start,DirectX::SimpleMath::Vector3 dropped, const int& max);

	/// <summary>
	/// フラグを削除
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void PickFlag();

	/// <summary>
	/// フラグ配列を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>フラグ配列</returns>
	std::vector<std::unique_ptr<Flag>>& GetFlags() { return m_flags; }

	/// <summary>
	/// 一番先頭のフラグが伸びきったらTrueを返す
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	bool IsFirstArrived();

	/// <summary>
	/// 一番先頭のパスの座標を取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	const DirectX::SimpleMath::Vector3& GetFirstPath();
};

#endif // FLAGMANAGER