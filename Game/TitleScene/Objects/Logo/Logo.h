/*
 *  @File   Logo.h
 *  @Brief  �^�C�g�����S�B
 *  @Date   2024-02-16
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef LOGO
#define LOGO

class DrawSprite;
class Logo
{
private:

	// ��ʔ䗦
	DirectX::SimpleMath::Vector2 m_screenRate;

	// �X�v���C�g�`��
	std::unique_ptr<DrawSprite> m_sprite;

	// ���W
	DirectX::SimpleMath::Vector2 m_position;

	// �g�嗦
	DirectX::SimpleMath::Vector2  m_rate;

	// �F
	DirectX::SimpleMath::Vector4 m_color;

private:

	// �摜�T�C�Y
	static const RECT_U SIZE;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="scRate">��ʔ䗦</param>
	/// <returns>�Ȃ�</returns>
	Logo(DirectX::SimpleMath::Vector2 scRate);
	~Logo();

	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="pos">���W</param>
	/// <param name="color">�F</param>
	/// <param name="rate">�g�嗦</param>
	/// <returns>�Ȃ�</returns>
	void Initialize(DirectX::SimpleMath::Vector2 pos, DirectX::SimpleMath::Vector4 color,
		DirectX::SimpleMath::Vector2 rate);

	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="��������"></param>
	/// <returns>�Ȃ�</returns>
	void Draw();

public:

	// �F���擾����
	DirectX::SimpleMath::Vector4 GetColor() const { return m_color; }
	// �F��ݒ肷��
	void SetColor(const DirectX::SimpleMath::Vector4& color) { m_color = color; }
};

#endif // LOGO