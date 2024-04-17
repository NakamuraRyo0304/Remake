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
public:

	// フラグを追加
	void AddFlag(DirectX::SimpleMath::Vector3 start, DirectX::SimpleMath::Vector3 dropped, const int& max);
	// フラグを削除
	void PickFlag();
	// フラグ配列を取得
	std::vector<std::unique_ptr<Flag>>& GetFlags() { return m_flags; }

	// 一番先頭のフラグが伸びきったらTrueを返す
	bool IsFirstArrived();

	// 一番先頭のパスの座標を取得
	const DirectX::SimpleMath::Vector3& GetFirstPath();

public:

	// コンストラクタ
	FlagManager();
	// デストラクタ
	~FlagManager();
	// 更新
	void Update();
	// 描画
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr);

private:

	// 旗の描画位置
	std::vector<std::unique_ptr<Flag>> m_flags;
	// 先頭座標
	DirectX::SimpleMath::Vector3 m_firstPosition;

};

#endif // FLAGMANAGER