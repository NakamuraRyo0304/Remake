/*
 *  @File   CursorObject.h
 *  @Brief  3D�J�[�\���̈ʒu�ɃI�u�W�F�N�g��`��B
 *  @Date   2024-02-04
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CURSOROBJECT
#define CURSOROBJECT

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class CursorObject : public IGameObject
{
private:

	// �J�[�\�����W
	DirectX::SimpleMath::Vector3 m_cursorPosition;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="path">���f���p�X</param>
	/// <param name="scale">�X�P�[��</param>
	/// <returns>�Ȃ�</returns>
	CursorObject(const wchar_t* path = L"Resources/Models/CursorObj.cmo",
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One * 0.25f);
	~CursorObject();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update() override;
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="context">�R���e�L�X�g</param>
	/// <param name="states">�R�����X�e�[�g</param>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�v���W�F�N�V�����s��</param>
	/// <param name="wireframe">���C���[�t���[��</param>
	/// <param name="option">�V�F�[�_�[�������_��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

public:

	// �J�[�\�����W���擾
	const DirectX::SimpleMath::Vector3& GetCursorPosition() { return m_cursorPosition; }
	// �J�[�\�����W��ݒ�
	void SetCursorPosition(const DirectX::SimpleMath::Vector3& pos) { m_cursorPosition = pos; }

};

#endif // CURSOROBJECT