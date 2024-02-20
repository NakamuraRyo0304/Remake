/*
 *  @File   DrawKeys.h
 *  @Brief  �L�[�`��B
 *  @Date   2024-02-21
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef DRAWKEYS
#define DRAWKEYS

class DrawSprite;
class DrawKeys
{
private:

	// �X�v���C�g
	std::unique_ptr<DrawSprite> m_sprite;

	// ���W
	DirectX::SimpleMath::Vector2 m_position;

	// ��ʊg�嗦�A�g�嗦
	DirectX::SimpleMath::Vector2 m_scRate, m_rate;

	// �F
	DirectX::SimpleMath::Vector4 m_color;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="path">�摜�p�X</param>
	/// <param name="pos">���W</param>
	/// <param name="screenRate">��ʔ䗦</param>
	/// <returns>�Ȃ�</returns>
	DrawKeys(const wchar_t* path, const DirectX::SimpleMath::Vector2& pos, const DirectX::SimpleMath::Vector2& screenRate);
	~DrawKeys();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();

public:

	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color){ m_color = color; }

	// �g�嗦�̎擾
	const DirectX::SimpleMath::Vector2& GetRate() { return m_rate; }
	// �g�嗦�̐ݒ�
	void SetRate(const DirectX::SimpleMath::Vector2& rate) { m_rate = rate; }

};

#endif // DRAWKEYS