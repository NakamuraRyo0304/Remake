/*
 *	@File	Head.h
 *	@Brief	�v���C���[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef HEAD
#define HEAD

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"
// �v���C���[�X�e�[�g
#include "../MoveStates.h"

class Timer;
class Head : public BaseObject
{
public:

	// �X�e�[�g��ݒ肷��
	void SetStatus(const MoveStates& status) { m_states = status; }

	// �R���X�g���N�^
	Head();
	// �f�X�g���N�^
	~Head();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;

private:

	// ���f���̃X�P�[��
	static const float SCALE;
	// ��U��̋���
	static const float ROT_POWER;


private:

	// �v���C���[�X�e�[�g
	MoveStates m_states;
	// �^�C�}�[
	std::unique_ptr<Timer> m_timer;

};

#endif // HEAD