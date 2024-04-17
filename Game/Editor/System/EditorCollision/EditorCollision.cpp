/*
 *	@File	EditorCollision.cpp
 *	@Brief	�G�f�B�^�̓����蔻��B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "EditorCollision.h"

// �萔�̐ݒ�
const float EditorCollision::HIT_RADIUS = 0.5f;		// �����蔻��̔��a

// �R���X�g���N�^
EditorCollision::EditorCollision()
	:
	m_position()									// ���W
{
}

// �f�X�g���N�^
EditorCollision::~EditorCollision()
{
}

// �X�V
void EditorCollision::Update(IGameObject* object, ID setting)
{
	auto ms = Mouse::Get().GetState();

	// null�������珈�������Ȃ�
	if (UserUtility::IsNull(object)) return;

	// �����蔻��i���j
	if (UserUtility::CheckPointInSphere(m_position, HIT_RADIUS, object->GetPosition()))
	{
		if (ms.leftButton)
		{
			object->SetID(setting);
		}
	}
}