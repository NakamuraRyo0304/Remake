/*
 *	@File	Flag.h
 *	@Brief	���I�u�W�F�N�g
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAG
#define FLAG

 //==============================================================================
 // �e�I�u�W�F�N�g�N���X
 //==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Flag : public IGameObject
{
private:

	// �����ʒu
	DirectX::SimpleMath::Vector3 m_droppedPosition;

	// �����t���O
	bool is_arrive;

private:

	// �����݂Ȃ��l
	static const float CLOSED_MATCH;

	// �������x
	static const float FALL_SPEED;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="start">�J�n���W</param>
	/// <param name="dropped">�������W</param>
	/// <returns>�Ȃ�</returns>
	Flag(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& dropped);
	~Flag();

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

	// �����󋵂��擾(����������True)
	bool IsArrive() { return is_arrive; }
};

#endif // FLAG