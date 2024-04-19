/*
 *	@File	Flag.h
 *	@Brief	���I�u�W�F�N�g
 *	@Date	2024-02-06
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef FLAG
#define FLAG

// �e�I�u�W�F�N�g�N���X
#include "Game/Bases/BaseObject.h"

class Flag : public BaseObject
{
public:

	// �����󋵂��擾(����������True)
	bool IsArrive() const { return is_arrive; }

	// �R���X�g���N�^
	Flag(const DirectX::SimpleMath::Vector3& start, const DirectX::SimpleMath::Vector3& dropped);
	// �f�X�g���N�^
	~Flag();
	// �X�V
	void Update() override;
	// �`��
	void Draw(ID3D11DeviceContext1* context, DirectX::CommonStates& states, DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj,
		bool wireframe = false, ShaderLambda option = nullptr) override;


private:

	// �����݂Ȃ��l
	static const float CLOSED_MATCH;
	// �������x
	static const float FALL_SPEED;

private:

	// �����ʒu
	DirectX::SimpleMath::Vector3 m_droppedPosition;
	// �����t���O
	bool is_arrive;

};

#endif // FLAG