/*
 *	@File	ColliderHelper.cpp
 *	@Brief	当たり判定のヘルパークラス。
 *	@Date	2023-01-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Game/Common/IGameObject/IGameObject.h"
#include "ColliderHelper.h"

//==============================================================================
// コンストラクタ
//==============================================================================
ColliderHelper::ColliderHelper(const float& radius)
	: m_radius{ radius }
{
	m_aabbCollider = std::make_unique<JudgeCubeCube>();
}

//==============================================================================
// デストラクタ
//==============================================================================
ColliderHelper::~ColliderHelper()
{
	m_aabbCollider.reset();
}

//==============================================================================
// 当たり判定の更新
//==============================================================================
void ColliderHelper::Update()
{
	using AABB_PLANE = JudgeCubeCube::HITBIT;

	// 当たり判定の更新
	for (auto& objectB : m_collisionList)
	{
		for (auto& objectA : m_collisionList)
		{
			// 同じオブジェクトでは判定を取らない
			if (objectB == objectA) continue;

			// 重さ付与がなければ判定を取らない
			if (objectB->GetWeight() == NON_WEIGHT || objectA->GetWeight() == NON_WEIGHT) continue;

			// 球の判定を行う
			if (!UserUtility::CheckPointInSphere(
				objectB->GetPosition(), m_radius, objectA->GetPosition())) continue;

			// 立方体同士の判定を行う
			SimpleMath::Vector3 _objB = objectB->GetPosition();
			m_aabbCollider->CubeCheck(&_objB, objectA->GetPosition(),
				objectB->GetScale(), objectA->GetScale());

			// 変更後の座標を設定
			objectB->SetPosition(_objB);
		}
	}
}


// Debug::DrawString::GetInstance().DebugLog(L"右が当たった！！！！！");

//==============================================================================
// オブジェクトを追加する
//==============================================================================
void ColliderHelper::AddObject(IGameObject* object)
{
	m_collisionList.push_back(object);
}

//==============================================================================
// コンストラクタ
//==============================================================================
JudgeCubeCube::JudgeCubeCube()
	: m_hit{ HITBIT::None }
{
}

//==============================================================================
// デストラクタ
//==============================================================================
JudgeCubeCube::~JudgeCubeCube()
{
}

//==============================================================================
// キューブ同士の判定
//==============================================================================
void JudgeCubeCube::CubeCheck(SimpleMath::Vector3* obj1, SimpleMath::Vector3 obj2,
	SimpleMath::Vector3 sz1,SimpleMath::Vector3 sz2)
{
	// 当たり判定を取る
	if (!((*obj1).x - sz1.x / 2 < obj2.x + sz2.x / 2 && (*obj1).x + sz1.x / 2 > obj2.x - sz2.x / 2 &&
		(*obj1).z - sz1.z / 2 < obj2.z + sz2.z / 2 && (*obj1).z + sz1.z / 2 > obj2.z - sz2.z / 2 &&
		(*obj1).y - sz1.y / 2 < obj2.y + sz2.y / 2 && (*obj1).y + sz1.y / 2 > obj2.y - sz2.y / 2))
	{
		m_hit = HITBIT::None;
		return;
	}

	// 自身の幅と高さを計算
	SimpleMath::Vector3 _length;
	_length.x = ((*obj1).x + sz1.x / 2) - ((*obj1).x - sz1.x / 2);
	_length.y = ((*obj1).y + sz1.y / 2) - ((*obj1).y - sz1.y / 2);
	_length.z = ((*obj1).z + sz1.z / 2) - ((*obj1).z - sz1.z / 2);

	// 各方向のめり込み具合
	float _ratioL = (((*obj1).x + sz1.x / 2) - (obj2.x - sz2.x / 2)) / _length.x;
	float _ratioR = ((obj2.x + sz2.x / 2) - ((*obj1).x - sz1.x / 2)) / _length.x;
	float _ratioU = (((*obj1).y + sz1.y / 2) - (obj2.y - sz2.y / 2)) / _length.y;
	float _ratioD = ((obj2.y + sz2.y / 2) - ((*obj1).y - sz1.y / 2)) / _length.y;
	float _ratioF = (((*obj1).z + sz1.z / 2) - (obj2.z - sz2.z / 2)) / _length.z;
	float _ratioB = ((obj2.z + sz2.z / 2) - ((*obj1).z - sz1.z / 2)) / _length.z;

	// 最大値を算出
	float _max = std::max({ _ratioL,_ratioR,_ratioU,_ratioD,_ratioF,_ratioB });

	// 当っている位置を格納し、押し戻し処理を行う
	if (_max == _ratioL) { m_hit = HITBIT::Left;	}
	if (_max == _ratioR) { m_hit = HITBIT::Right;	}
	if (_max == _ratioU) { m_hit = HITBIT::Up;		}
	if (_max == _ratioD) { m_hit = HITBIT::Down;	}
	if (_max == _ratioF) { m_hit = HITBIT::Front;	}
	if (_max == _ratioB) { m_hit = HITBIT::Behind;	}

	// 押し戻しをする(衝突オブジェクトの座標＋サイズの半分)
	if (m_hit == HITBIT::Left)		{ (*obj1).x = obj2.x + (sz1 + sz2).x / 2; }
	if (m_hit == HITBIT::Right)		{ (*obj1).x = obj2.x - (sz1 + sz2).x / 2; }
	if (m_hit == HITBIT::Up)		{ (*obj1).y = obj2.y + (sz1 + sz2).y / 2; }
	if (m_hit == HITBIT::Down)		{ (*obj1).y = obj2.y - (sz1 + sz2).y / 2; }
	if (m_hit == HITBIT::Front)		{ (*obj1).z = obj2.z + (sz1 + sz2).z / 2; }
	if (m_hit == HITBIT::Behind)	{ (*obj1).z = obj2.z - (sz1 + sz2).z / 2; }
}