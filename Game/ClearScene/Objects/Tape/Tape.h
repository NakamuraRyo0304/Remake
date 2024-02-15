/*
 *  @File   Tape.h
 *  @Brief  �e�[�v�B
 *  @Date   2024-02-14
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef TAPE
#define TAPE

class DrawSprite;
class Tape
{
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

	// ���W/�g�嗦
	DirectX::SimpleMath::Vector2 m_position, m_rate, m_scRate;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	Tape();
	~Tape();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="rate">�X�v���C�g�g�嗦</param>
	/// <param name="scRate">�X�N���[���g�嗦</param>
	/// <param name="rotate">��]��</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector2 rate,
		DirectX::SimpleMath::Vector2 scRate, float rotate);

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();
};

#endif // TAPE