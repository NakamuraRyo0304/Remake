/*
 *  @File   Iceberg.h
 *  @Brief  �X�R�B
 *  @Date   2024-02-18
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef ICEBERG
#define ICEBERG

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Iceberg : public IGameObject
{
private:

	// ��]��
	float m_rotation;

	// ��]���x
	float m_speed;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">���W</param>
	/// <param name="rate">�g�嗦</param>
	/// <param name="speed">��]���x</param>
	/// <returns>�Ȃ�</returns>
	Iceberg(DirectX::SimpleMath::Vector3 position, float rate, float speed);
	~Iceberg();

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

};

#endif // ICEBERG