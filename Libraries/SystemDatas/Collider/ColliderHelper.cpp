/*
 *	@File	ColliderHelper.cpp
 *	@Brief	�����蔻��̃w���p�[�N���X�B
 *	@Date	2023-01-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Game/Common/IGameObject/IGameObject.h"
#include "ColliderHelper.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
ColliderHelper::ColliderHelper(const float& radius)
	: m_radius{ radius }
{
	m_aabbCollider = std::make_unique<JudgeCubeCube>();
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
ColliderHelper::~ColliderHelper()
{
	m_aabbCollider.reset();
}

//==============================================================================
// �����蔻��̍X�V
//==============================================================================
void ColliderHelper::Update()
{
	using AABB_PLANE = JudgeCubeCube::HITBIT;

	// �����蔻��̍X�V
	for (auto& objectB : m_collisionList)
	{
		for (auto& objectA : m_collisionList)
		{
			// �����I�u�W�F�N�g�ł͔�������Ȃ�
			if (objectB == objectA) continue;

			// �d���t�^���Ȃ���Δ�������Ȃ�
			if (objectB->GetWeight() == NON_WEIGHT || objectA->GetWeight() == NON_WEIGHT) continue;

			// ���̔�����s��
			if (!UserUtility::CheckPointInSphere(
				objectB->GetPosition(), m_radius, objectA->GetPosition())) continue;

			// �����̓��m�̔�����s��
			SimpleMath::Vector3 _objB = objectB->GetPosition();
			m_aabbCollider->CubeCheck(&_objB, objectA->GetPosition(),
				objectB->GetScale(), objectA->GetScale());

			// �ύX��̍��W��ݒ�
			objectB->SetPosition(_objB);
		}
	}
}


// Debug::DrawString::GetInstance().DebugLog(L"�E�����������I�I�I�I�I");

//==============================================================================
// �I�u�W�F�N�g��ǉ�����
//==============================================================================
void ColliderHelper::AddObject(IGameObject* object)
{
	m_collisionList.push_back(object);
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
JudgeCubeCube::JudgeCubeCube()
	: m_hit{ HITBIT::None }
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
JudgeCubeCube::~JudgeCubeCube()
{
}

//==============================================================================
// �L���[�u���m�̔���
//==============================================================================
void JudgeCubeCube::CubeCheck(SimpleMath::Vector3* obj1, SimpleMath::Vector3 obj2,
	SimpleMath::Vector3 sz1,SimpleMath::Vector3 sz2)
{
	// �����蔻������
	if (!((*obj1).x - sz1.x / 2 < obj2.x + sz2.x / 2 && (*obj1).x + sz1.x / 2 > obj2.x - sz2.x / 2 &&
		(*obj1).z - sz1.z / 2 < obj2.z + sz2.z / 2 && (*obj1).z + sz1.z / 2 > obj2.z - sz2.z / 2 &&
		(*obj1).y - sz1.y / 2 < obj2.y + sz2.y / 2 && (*obj1).y + sz1.y / 2 > obj2.y - sz2.y / 2))
	{
		m_hit = HITBIT::None;
		return;
	}

	// ���g�̕��ƍ������v�Z
	SimpleMath::Vector3 _length;
	_length.x = ((*obj1).x + sz1.x / 2) - ((*obj1).x - sz1.x / 2);
	_length.y = ((*obj1).y + sz1.y / 2) - ((*obj1).y - sz1.y / 2);
	_length.z = ((*obj1).z + sz1.z / 2) - ((*obj1).z - sz1.z / 2);

	// �e�����̂߂荞�݋
	float _ratioL = (((*obj1).x + sz1.x / 2) - (obj2.x - sz2.x / 2)) / _length.x;
	float _ratioR = ((obj2.x + sz2.x / 2) - ((*obj1).x - sz1.x / 2)) / _length.x;
	float _ratioU = (((*obj1).y + sz1.y / 2) - (obj2.y - sz2.y / 2)) / _length.y;
	float _ratioD = ((obj2.y + sz2.y / 2) - ((*obj1).y - sz1.y / 2)) / _length.y;
	float _ratioF = (((*obj1).z + sz1.z / 2) - (obj2.z - sz2.z / 2)) / _length.z;
	float _ratioB = ((obj2.z + sz2.z / 2) - ((*obj1).z - sz1.z / 2)) / _length.z;

	// �ő�l���Z�o
	float _max = std::max({ _ratioL,_ratioR,_ratioU,_ratioD,_ratioF,_ratioB });

	// �����Ă���ʒu���i�[���A�����߂��������s��
	if (_max == _ratioL) { m_hit = HITBIT::Left;	}
	if (_max == _ratioR) { m_hit = HITBIT::Right;	}
	if (_max == _ratioU) { m_hit = HITBIT::Up;		}
	if (_max == _ratioD) { m_hit = HITBIT::Down;	}
	if (_max == _ratioF) { m_hit = HITBIT::Front;	}
	if (_max == _ratioB) { m_hit = HITBIT::Behind;	}

	// �����߂�������(�Փ˃I�u�W�F�N�g�̍��W�{�T�C�Y�̔���)
	if (m_hit == HITBIT::Left)		{ (*obj1).x = obj2.x + (sz1 + sz2).x / 2; }
	if (m_hit == HITBIT::Right)		{ (*obj1).x = obj2.x - (sz1 + sz2).x / 2; }
	if (m_hit == HITBIT::Up)		{ (*obj1).y = obj2.y + (sz1 + sz2).y / 2; }
	if (m_hit == HITBIT::Down)		{ (*obj1).y = obj2.y - (sz1 + sz2).y / 2; }
	if (m_hit == HITBIT::Front)		{ (*obj1).z = obj2.z + (sz1 + sz2).z / 2; }
	if (m_hit == HITBIT::Behind)	{ (*obj1).z = obj2.z - (sz1 + sz2).z / 2; }
}