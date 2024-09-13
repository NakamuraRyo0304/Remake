/*
 *  @File   CursorObject.cpp
 *  @Brief  3D�J�[�\���̈ʒu�ɃI�u�W�F�N�g��`��B
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "CursorObject.h"

// �R���X�g���N�^
CursorObject::CursorObject(const wchar_t* path, SimpleMath::Vector3 scale)
	:
	BaseObject(path, L"Resources/Models")
{
	CreateModel();
	SetID(ID::PE_Cursor_Object);
	SetPosition(SimpleMath::Vector3::Zero);
	SetInitialPosition(GetPosition());
	SetRotate(SimpleMath::Vector3::Zero);
	SetScale(scale);
	SetInitialScale(GetScale());
}

// �f�X�g���N�^
CursorObject::~CursorObject()
{
	ReleaseModel();
}

// �X�V
void CursorObject::Update()
{
	// ���W��ݒ肷��
	SetPosition(m_cursorPosition);

	// �}�g���N�X���쐬
	CreateWorldMatrix();
}

// �`��
void CursorObject::Draw(ID3D11DeviceContext1* context, CommonStates& states,
	SimpleMath::Matrix& view, SimpleMath::Matrix& proj, bool wireframe, ShaderLambda option)
{
	GetModel()->Draw(context, states, GetWorldMatrix() * GetParentMatrix(), view, proj, wireframe, option);
}
