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
private:

	// ���C
	std::unique_ptr<RayCast> m_ray;

	// ���[���h�}�E�X�̍��W
	DirectX::SimpleMath::Vector3 m_position;

	// ����
	int m_height;

	// �v���C���[�h
	bool is_playing;

private:

	// �ō����x
	static const float MAX_HEIGHT;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	WorldMouse();
	~WorldMouse();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	void Draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	// ���[���h�}�E�X�̍��W���擾
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	// �v���C���[�h�ɂ���
	void ToPlayMode() { is_playing = true; }
	// �G�f�B�^���[�h�ɂ���
	void ToEditMode() { is_playing = false; }
};

#endif // WORLDMOUSE