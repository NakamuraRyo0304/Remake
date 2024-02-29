/*
 *	@File	Head.h
 *	@Brief	�v���C���[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef HEAD
#define HEAD

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

//==============================================================================
// �v���C���[�X�e�[�g
//==============================================================================
#include "../MoveStates.h"

class Timer;
class Head : public IGameObject
{
private:

	// �v���C���[�X�e�[�g
	MoveStates m_states;

	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;

private:

	// ���f���̃X�P�[��
	static const float SCALE;

	// ��U��̋���
	static const float ROT_POWER;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Head();
	~Head();

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

	// �X�e�[�g��ݒ肷��
	void SetStatus(const MoveStates& status) { m_states = status; }

};

#endif // HEAD