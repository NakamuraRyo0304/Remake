/*
 *	@File	ColliderHelper.h
 *	@Brief	�����蔻��̃w���p�[�N���X�B
 *	@Date	2023-01-09
 *  @Author NakamuraRyo
 */

#pragma once

#ifndef JUDGECUBECUBE
#define JUDGECUBECUBE

//==============================================================================
// �����̔���(AABB)
//==============================================================================
class JudgeCubeCube
{
public:

	// �Փ˖�
	enum class HITBIT : UINT
	{
		None,
		Left,
		Right,
		Up,
		Down,
		Front,
		Behind,
	};

private:

	// �Փ˖ʂ̕ۊ�
	HITBIT m_hit;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	JudgeCubeCube();
	~JudgeCubeCube();

	// �Փ˖ʂ��擾
	HITBIT GetHitBit() { return m_hit; }

	/// <summary>
	/// �����蔻��̃`�F�b�N
	/// </summary>
	/// <param name="obj1">�I�u�W�F�P</param>
	/// <param name="obj2">�I�u�W�F�Q</param>
	/// <param name="sz1">�T�C�Y�P</param>
	/// <param name="sz2">�T�C�Y�Q</param>
	/// <returns>�Ȃ�</returns>
	void CubeCheck(DirectX::SimpleMath::Vector3* obj1, DirectX::SimpleMath::Vector3 obj2,
		DirectX::SimpleMath::Vector3 sz1, DirectX::SimpleMath::Vector3 sz2);
};

#endif // JUDGECUBECUBE

#ifndef COLLIDERHELPER
#define COLLIDERHELPER

//==============================================================================
// �t�@�C���̃C���N���[�h
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class ColliderHelper
{
private:

	// ������s�����a
	float m_radius;

	// ������s���I�u�W�F�N�g�z��
	std::vector<IGameObject*> m_collisionList;

	// �Փ˔���`�F�b�J�[�iAABB�j
	std::unique_ptr<JudgeCubeCube> m_aabbCollider;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="radius">����̔��a</param>
	/// <returns>�Ȃ�</returns>
	ColliderHelper(const float& radius);
	~ColliderHelper();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �I�u�W�F�N�g��ǉ�����
	/// </summary>
	/// <param name="object">���������I�u�W�F�N�g�̃|�C���^</param>
	/// <returns>�Ȃ�</returns>
	void AddObject(IGameObject* object);

};

#endif // COLLIDERHELPER
