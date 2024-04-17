/*
 *  @File   FlagManager.cpp
 *  @Brief  旗管理クラス。
 *  @Date   2024-02-06
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "../../Objects/Flag/Flag.h"	// フラグ
#include  "Libraries/UserUtility.h"
#include "FlagManager.h"

// コンストラクタ
FlagManager::FlagManager()
	:
	m_firstPosition()		// 先頭座標
{
}

// デストラクタ
FlagManager::~FlagManager()
{
	m_flags.clear();
}

// 更新
void FlagManager::Update()
{
	if (m_flags.empty()) return;

	// 先頭座標を保存
	m_firstPosition = m_flags[0]->GetPosition();

	for (int i = 0; i < m_flags.size(); i++)
	{
		m_flags[i]->Update();
	}
}

// 描画
void FlagManager::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	if (m_flags.empty()) return;

	for (int i = 0; i < m_flags.size(); i++)
	{
		m_flags[i]->Draw(context, states, view, proj, wireframe, option);
	}
}

// フラグを追加
void FlagManager::AddFlag(SimpleMath::Vector3 start, SimpleMath::Vector3 dropped, const int& max)
{
	// 最大数を越えたら追加しない
	if (m_flags.size() >= max) return;

	m_flags.push_back(std::make_unique<Flag>(start, dropped));
}

// フラグを削除
void FlagManager::PickFlag()
{
	UserUtility::RemoveVec(m_flags, m_flags[0]);
}

// 先頭のフラグが生えきったらTRUE
bool FlagManager::IsFirstArrived()
{
	if (m_flags.empty()) return false;

	if (m_flags[0]->IsArrive())
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 先頭の座標を取得
const SimpleMath::Vector3& FlagManager::GetFirstPath()
{
	if (m_flags.empty()) return SimpleMath::Vector3::Zero;

	return m_firstPosition;
}
