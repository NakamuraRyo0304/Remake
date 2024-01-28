/*
 *	@File	EditorCollision.cpp
 *	@Brief	�G�f�B�^�̓����蔻��B
 *	@Date	2023-01-28
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Game/Editor/System/WorldMouse/WorldMouse.h"
#include "Libraries/UserUtility.h"
#include "EditorCollision.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const float EditorCollision::HIT_RADIUS = 0.5f;		// �����蔻��̔��a

//==============================================================================
// �R���X�g���N�^
//==============================================================================
EditorCollision::EditorCollision(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// ���[���h�}�E�X�쐬
	m_worldMouse = std::make_unique<WorldMouse>(view, proj);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
EditorCollision::~EditorCollision()
{
}

//==============================================================================
// �X�V����
//==============================================================================
void EditorCollision::Update(IGameObject* object, ID setting)
{
	auto _mouse = Mouse::Get().GetState();

	// ���[���h�}�E�X�̍X�V
	m_worldMouse->Update();

	// �����蔻��i���j
	if (UserUtility::CheckPointInSphere(m_worldMouse->GetPosition(), HIT_RADIUS, object->GetPosition()))
	{
		if (_mouse.leftButton)
		{
			object->SetID(setting);
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void EditorCollision::Draw(SimpleMath::Matrix view, SimpleMath::Matrix proj)
{
	// �`��֘A����
	m_worldMouse->Draw(view, proj);
}
