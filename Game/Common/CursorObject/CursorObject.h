/*
 *  @File   CursorObject.h
 *  @Brief  3D�J�[�\���̈ʒu�ɃI�u�W�F�N�g��`��B
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CURSOROBJECT
#define CURSOROBJECT

// �e�I�u�W�F�N�g�N���X
#include "Game/Common/IGameObject/IGameObject.h"

class CursorObject : public IGameObject
{
public:

	// �J�[�\�����W���擾
	DirectX::SimpleMath::Vector3 GetCursorPosition() const { return m_cursorPosition; }
	// �J�[�\�����W��ݒ�
	void SetCursorPosition(const DirectX::SimpleMath::Vector3& pos) { m_cursorPosition = pos; }

	// �R���X�g���N�^
	CursorObject(const wchar_t* path = L"Resources/Models/CursorObj.cmo",
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One * 0.25f);
	// �f�X�g���N�^
	~CursorObject();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// �J�[�\�����W
	DirectX::SimpleMath::Vector3 m_cursorPosition;

};

#endif // CURSOROBJECT