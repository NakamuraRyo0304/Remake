/*
 *	@File	Cloud.h
 *	@Brief	�_�u���b�N�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef CLOUD
#define CLOUD

//==============================================================================
// �e�I�u�W�F�N�g�N���X
//==============================================================================
#include "Game/Common/IGameObject/IGameObject.h"

class Timer;
class Cloud : public IGameObject
{
private:

	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;

	// �Փ˃t���O
	bool is_hit;

private:

	// ���쎞��
	static const float LIMIT;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">�������W</param>
	/// <returns>�Ȃ�</returns>
	Cloud(DirectX::SimpleMath::Vector3 position);
	~Cloud();

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

	// �Փ˒ʒm
	void SetHitFlag(const bool& isHit) { is_hit = isHit; }

};

#endif // CLOUD