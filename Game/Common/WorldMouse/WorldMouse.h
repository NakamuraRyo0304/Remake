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

	// �r���[�s��A�ˉe�s��
	DirectX::SimpleMath::Matrix m_view, m_projection;

	// ���[���h�}�E�X�̍��W
	DirectX::SimpleMath::Vector3 m_position;

	// ����
	float m_height;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="view">�r���[�s��</param>
	/// <param name="proj">�ˉe�s��</param>
	/// <returns>�Ȃ�</returns>
	WorldMouse(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
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
};

#endif // WORLDMOUSE