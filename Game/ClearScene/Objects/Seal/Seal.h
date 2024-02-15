/*
 *  @File   Seal.h
 *  @Brief  �V�[���B
 *  @Date   2024-02-15
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef SEAL
#define SEAL

class DrawSprite;
class Seal
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
	/// <param name="path">�V�[���Ɏg���摜�p�X</param>
	/// <returns>�Ȃ�</returns>
	Seal(const wchar_t* path);
	~Seal();

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

#endif // SEAL