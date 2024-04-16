/*
 *	@File	WorldMouse.h
 *	@Brief	���[���h�ϊ������}�E�X�B
 *	@Date	2023-01-27
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef WORLDMOUSE
#define WORLDMOUSE

class RayCast;
class WorldMouse
{
public:

	// ���[���h�}�E�X�̍��W���擾
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

	// �v���C���[�h�ɂ���
	void ToPlayMode() { is_playing = true; }
	// �G�f�B�^���[�h�ɂ���
	void ToEditMode() { is_playing = false; }

	// �R���X�g���N�^
	WorldMouse();
	// �f�X�g���N�^
	~WorldMouse();
	// �X�V
	void Update();
	// �`��
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:

	// �ō����x
	static const float MAX_HEIGHT;
	// �v���C���̍���
	static const float PLAY_HEIGHT;

private:

	// ���C
	std::unique_ptr<RayCast> m_ray;
	// ���[���h�}�E�X�̍��W
	DirectX::SimpleMath::Vector3 m_position;
	// ����
	int m_height;
	// �v���C���[�h
	bool is_playing;

};

#endif // WORLDMOUSE